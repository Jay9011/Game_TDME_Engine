#pragma once

#include "Core/CoreMacros.h"
#include "TVector3.h"

#include <algorithm>
#include <cmath>

namespace TDME
{
    /**
     * @brief Quaternion 클래스
     * @details 오일러 회전에 의한 문제를 해결하기 위해 Quaternion을 사용.
     * @tparam T Quaternion 요소 타입
     */
    template <typename T>
    struct TQuaternion
    {
        T X, Y, Z, W; // Quaternion은 4차원 벡터로 표현되며, X, Y, Z는 회전 축을 나타내고 W는 회전 각도를 나타냄.

        constexpr TQuaternion() : X(T(0)), Y(T(0)), Z(T(0)), W(T(1)) {}
        constexpr TQuaternion(T x, T y, T z, T w) : X(x), Y(y), Z(z), W(w) {}

        /**
         * @brief 쿼터니언의 길이를 반환
         * @return T 쿼터니언의 길이값
         */
        constexpr T Length() const
        {
            return std::sqrt(LengthSquared());
        }

        /**
         * @brief 쿼터니언의 길이의 제곱을 반환
         * @return T 쿼터니언의 길이의 제곱값
         */
        constexpr T LengthSquared() const
        {
            return X * X + Y * Y + Z * Z + W * W;
        }

        /**
         * @brief 쿼터니언을 정규화
         * @details 쿼터니언의 길이가 1이 되도록 정규화
         */
        constexpr void Normalize()
        {
            T len = Length();
            if (len > T(0))
            {
                T invLen = T(1) / len;
                X *= invLen;
                Y *= invLen;
                Z *= invLen;
                W *= invLen;
            }
        }

        /**
         * @brief 정규화된 쿼터니언 복사본을 반환
         * @return TQuaternion 정규화된 쿼터니언
         */
        [[nodiscard]] constexpr TQuaternion Normalized() const
        {
            TQuaternion result = *this;
            result.Normalize();
            return result;
        }

        /**
         * @brief 쿼터니언의 켤레(Conjugate)를 반환
         * @return TQuaternion 쿼터니언의 켤레
         */
        constexpr TQuaternion Conjugate() const
        {
            return TQuaternion(-X, -Y, -Z, W);
        }

        /**
         * @brief 역쿼터니언
         * @return TQuaternion 쿼터니언의 역
         */
        [[nodiscard]] constexpr TQuaternion Inverse() const
        {
            T lenSquared = LengthSquared();
            if (lenSquared > T(0))
            {
                T invLen = T(1) / lenSquared;
                return TQuaternion(-X * invLen, -Y * invLen, -Z * invLen, W * invLen);
            }
            return *this;
        }

        /**
         * @brief 쿼터니언을 축과 각도로 변환
         * @param outAxis 회전 축
         * @param outAngleRad 회전 각도 (라디안)
         */
        constexpr void ToAxisAngle(TVector3<T>& outAxis, T& outAngleRad) const
        {
            // W = cos(theta / 2), 따라서 theta = 2 * std::acos(W)
            outAngleRad = T(2) * std::acos(std::clamp(W, T(-1), T(1)));

            T sinHalfAngle = std::sqrt(T(1) - W * W);

            if (sinHalfAngle > T(0.0001))
            {
                outAxis.X = X / sinHalfAngle;
                outAxis.Y = Y / sinHalfAngle;
                outAxis.Z = Z / sinHalfAngle;
            }
            else
            {
                // 각도가 0에 가까우면 축은 정의되지 않음, 따라서 임의의 축을 선택
                outAxis = TVector3<T>(1, 0, 0);
            }
        }

        /**
         * @brief 벡터를 쿼터니언으로 회전
         * @param v 회전할 벡터
         * @return TVector3<T> 회전된 벡터
         */
        constexpr TVector3<T> RotateVector(const TVector3<T>& v) const
        {
            // q * v * q^(-1) 공식 최적화
            TVector3<T> qv(X, Y, Z);
            TVector3<T> uv  = qv.Cross(v);
            TVector3<T> uuv = qv.Cross(uv);

            return v + (uv * W + uuv) * T(2);
        }

        //////////////////////////////////////////////////////////////
        // 정적 함수
        //////////////////////////////////////////////////////////////

        /**
         * @brief 쿼터니언의 내적을 반환
         * @param q1 첫 번째 쿼터니언
         * @param q2 두 번째 쿼터니언
         * @return T 쿼터니언의 내적값
         */
        static constexpr T Dot(const TQuaternion& q1, const TQuaternion& q2)
        {
            return q1.X * q2.X + q1.Y * q2.Y + q1.Z * q2.Z + q1.W * q2.W;
        }

        /**
         * @brief 구면 선형 보간 (Spherical Linear Interpolation)
         * @param q1 첫 번째 쿼터니언
         * @param q2 두 번째 쿼터니언
         * @param t 보간 계수 (0.0 ~ 1.0)
         * @return TQuaternion 구면 선형 보간 결과
         */
        static TQuaternion Slerp(const TQuaternion& a, const TQuaternion& b, T t)
        {
            T dot = Dot(a, b);

            // 최단 경로 선택
            TQuaternion b2 = b;
            if (dot < T(0))
            {
                b2  = -b;
                dot = -dot;
            }

            // dot이 1에 가까우면 선형 보간 사용
            if (dot > T(0.9995))
            {
                TQuaternion result = a + (b2 - a) * t;
                return result.Normalized();
            }

            // Slerp
            T theta    = std::acos(dot);
            T sinTheta = std::sin(theta);
            T wa       = std::sin((T(1) - t) * theta) / sinTheta;
            T wb       = std::sin(t * theta) / sinTheta;

            return TQuaternion(
                a.X * wa + b2.X * wb, // X
                a.Y * wa + b2.Y * wb, // Y
                a.Z * wa + b2.Z * wb, // Z
                a.W * wa + b2.W * wb  // W
            );
        }

        //////////////////////////////////////////////////////////////
        // 팩토리 메서드
        //////////////////////////////////////////////////////////////

        /**
         * @brief 축과 각도를 사용하여 Quaternion을 생성
         * @param axis 회전 축
         * @param angleRad 회전 각도 (라디안)
         * @return TQuaternion 축과 각도를 사용하여 생성된 Quaternion
         */
        static constexpr TQuaternion FromAxisAngle(const TVector3<T>& axis, T angleRad)
        {
            T halfAngle = angleRad * T(0.5);
            T sinHalf   = std::sin(halfAngle);
            T cosHalf   = std::cos(halfAngle);

            return TQuaternion(axis.X * sinHalf, axis.Y * sinHalf, axis.Z * sinHalf, cosHalf);
        }

        /**
         * @brief 오일러 각도를 사용하여 Quaternion을 생성
         * @details Pitch = X, Yaw = Y, Roll = Z (Roll -> Pitch -> Yaw 순서)
         * @param pitch 피치 각도 (라디안)
         * @param yaw 요 각도 (라디안)
         * @param roll 롤 각도 (라디안)
         * @return TQuaternion 오일러 각도를 사용하여 생성된 Quaternion
         */
        static constexpr TQuaternion FromEuler(T pitch, T yaw, T roll)
        {
            T halfPitch = pitch * T(0.5); // X
            T halfYaw   = yaw * T(0.5);   // Y
            T halfRoll  = roll * T(0.5);  // Z

            T cosPitch = std::cos(halfPitch);
            T sinPitch = std::sin(halfPitch);
            T cosYaw   = std::cos(halfYaw);
            T sinYaw   = std::sin(halfYaw);
            T cosRoll  = std::cos(halfRoll);
            T sinRoll  = std::sin(halfRoll);

            return TQuaternion(
                cosYaw * sinPitch * cosRoll + sinYaw * cosPitch * sinRoll, // X
                sinYaw * cosPitch * cosRoll - cosYaw * sinPitch * sinRoll, // Y
                cosYaw * cosPitch * sinRoll - sinYaw * sinPitch * cosRoll, // Z
                cosYaw * cosPitch * cosRoll + sinYaw * sinPitch * sinRoll  // W
            );
        }

        /**
         * @brief X축을 기준으로 회전하는 Quaternion을 생성
         * @param angleRad 회전 각도 (라디안)
         * @return TQuaternion X축을 기준으로 회전하는 Quaternion
         */
        static constexpr TQuaternion FromRotationX(T angleRad)
        {
            T halfAngle = angleRad * T(0.5);
            return TQuaternion(std::sin(halfAngle), T(0), T(0), std::cos(halfAngle));
        }

        /**
         * @brief Y축을 기준으로 회전하는 Quaternion을 생성
         * @param angleRad 회전 각도 (라디안)
         * @return TQuaternion Y축을 기준으로 회전하는 Quaternion
         */
        static constexpr TQuaternion FromRotationY(T angleRad)
        {
            T halfAngle = angleRad * T(0.5);
            return TQuaternion(T(0), std::sin(halfAngle), T(0), std::cos(halfAngle));
        }

        /**
         * @brief Z축을 기준으로 회전하는 Quaternion을 생성
         * @param angleRad 회전 각도 (라디안)
         * @return TQuaternion Z축을 기준으로 회전하는 Quaternion
         */
        static constexpr TQuaternion FromRotationZ(T angleRad)
        {
            T halfAngle = angleRad * T(0.5);
            return TQuaternion(T(0), T(0), std::sin(halfAngle), std::cos(halfAngle));
        }

        //////////////////////////////////////////////////////////////
        // 연산자 오버로딩
        //////////////////////////////////////////////////////////////

        /**
         * @brief 쿼터니언 덧셈 (보간용)
         * @param other 다른 Quaternion
         * @return TQuaternion 쿼터니언 덧셈 결과
         */
        constexpr TQuaternion operator+(const TQuaternion& other) const
        {
            return TQuaternion(X + other.X, Y + other.Y, Z + other.Z, W + other.W);
        }

        /**
         * @brief 쿼터니언 뺄셈
         * @param other 다른 Quaternion
         * @return TQuaternion 쿼터니언 뺄셈 결과
         */
        constexpr TQuaternion operator-(const TQuaternion& other) const
        {
            return TQuaternion(X - other.X, Y - other.Y, Z - other.Z, W - other.W);
        }

        /**
         * @brief 쿼터니언 부호 변환 (부정)
         * @details q와 -q는 같은 회전을 나타냄. Slerp 최단 경로 계산에 사용.
         */
        constexpr TQuaternion operator-() const
        {
            return TQuaternion(-X, -Y, -Z, -W);
        }

        /**
         * @brief 쿼터니언 스칼라 곱
         * @param scalar 스칼라값
         * @return TQuaternion 쿼터니언 스칼라 곱 결과
         */
        constexpr TQuaternion operator*(T scalar) const
        {
            return TQuaternion(X * scalar, Y * scalar, Z * scalar, W * scalar);
        }

        /**
         * @brief 쿼터니언 스칼라 곱을 계산하여 자기 자신에 저장
         * @param scalar 스칼라값
         * @return TQuaternion& 자기 자신의 참조
         */
        constexpr TQuaternion& operator*=(T scalar)
        {
            X *= scalar;
            Y *= scalar;
            Z *= scalar;
            W *= scalar;
            return *this;
        }

        /**
         * @brief 쿼터니언 곱셈 (회전 합성)
         * @details q1 * q2 = q2 회전 후 q1 회전
         * @param other 다른 Quaternion
         * @return TQuaternion 두 Quaternion의 곱
         */
        constexpr TQuaternion operator*(const TQuaternion& other) const
        {
            return TQuaternion(
                W * other.X + X * other.W + Y * other.Z - Z * other.Y, // X
                W * other.Y - X * other.Z + Y * other.W + Z * other.X, // Y
                W * other.Z + X * other.Y - Y * other.X + Z * other.W, // Z
                W * other.W - X * other.X - Y * other.Y - Z * other.Z  // W
            );
        }

        /**
         * @brief 쿼터니언 곱셈을 계산하여 자기 자신에 저장
         * @param other 다른 Quaternion
         * @return TQuaternion& 자기 자신의 참조
         */
        TQuaternion& operator*=(const TQuaternion& other)
        {
            *this = *this * other;
            return *this;
        }

        /**
         * @brief 쿼터니언이 같은지 비교
         * @param other 다른 Quaternion
         * @return bool 쿼터니언이 같은지 여부
         */
        constexpr bool operator==(const TQuaternion& other) const
        {
            return X == other.X && Y == other.Y && Z == other.Z && W == other.W;
        }

        /**
         * @brief 쿼터니언이 다른지 비교
         * @param other 다른 Quaternion
         * @return bool 쿼터니언이 다른지 여부
         */
        constexpr bool operator!=(const TQuaternion& other) const
        {
            return !(*this == other);
        }

        //////////////////////////////////////////////////////////////
        // 미리 정의된 Quaternion
        //////////////////////////////////////////////////////////////

        static constexpr TQuaternion Identity()
        {
            return TQuaternion(T(0), T(0), T(0), T(1));
        }
    }; // struct TQuaternion

    //////////////////////////////////////////////////////////////
    // 타입 별칭
    //////////////////////////////////////////////////////////////

    using Quaternion  = TQuaternion<float>;
    using QuaternionD = TQuaternion<double>;

    namespace Quaternions
    {
        INLINE constexpr Quaternion IDENTITY = Quaternion::Identity();
    } // namespace Quaternions

} // namespace TDME