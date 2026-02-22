#pragma once

#include "TVector2.h"
#include "TVectorOperations.h"

namespace TDME
{
    /**
     * @brief 3차원 벡터 클래스
     * @details TVectorOperations 템플릿에 자기 자신을 파생 클래스로 캐스팅하여 사용합니다.
     * @tparam T 벡터 요소 타입
     */
    template <typename T>
    struct TVector3 : TVectorOperations<TVector3<T>, T, 3>
    {
#pragma warning(push)
#pragma warning(disable : 4201) // 익명 구조체/공용체 사용에 대한 경고 비활성화
        union
        {
            struct
            {
                T X, Y, Z;
            };
            struct
            {
                T R, G, B;
            };
            T Data[3];
        };
#pragma warning(pop)

        constexpr TVector3() : X(T(0)), Y(T(0)), Z(T(0)) {}
        constexpr TVector3(T x, T y, T z) : X(x), Y(y), Z(z) {}

        /**
         * @brief 스칼라값으로 초기화
         * @param scalar 스칼라값
         * @return TVector3 스칼라값으로 초기화된 벡터
         */
        explicit constexpr TVector3(T scalar) : X(scalar), Y(scalar), Z(scalar) {}

        /**
         * @brief 2차원 벡터에서 Z 값을 추가하여 3차원 벡터로 변환
         * @param v2 2차원 벡터
         * @param z Z 값 (기본값: 0)
         * @return TVector3 3차원 벡터
         */
        constexpr TVector3(const TVector2<T>& v2, T z = T(0)) : X(v2.X), Y(v2.Y), Z(z) {}

        /**
         * @brief 3차원 외적 계산
         * @param other 다른 벡터
         * @return TVector3 외적값
         */
        constexpr TVector3 Cross(const TVector3& other) const
        {
            return TVector3(
                Y * other.Z - Z * other.Y,
                Z * other.X - X * other.Z,
                X * other.Y - Y * other.X);
        }

        /**
         * @brief XY 평면으로 반환
         * @return TVector2<T> XY 평면으로 반화된 2차원 벡터
         */
        constexpr TVector2<T> XY() const
        {
            return TVector2<T>(X, Y);
        }

        //////////////////////////////////////////////////////////////
        // 미리 정의된 벡터
        //////////////////////////////////////////////////////////////

        static constexpr TVector3 Zero() { return TVector3(T(0), T(0), T(0)); }
        static constexpr TVector3 One() { return TVector3(T(1), T(1), T(1)); }
        static constexpr TVector3 UnitX() { return TVector3(T(1), T(0), T(0)); }
        static constexpr TVector3 UnitY() { return TVector3(T(0), T(1), T(0)); }
        static constexpr TVector3 UnitZ() { return TVector3(T(0), T(0), T(1)); }
        static constexpr TVector3 Right() { return TVector3(T(1), T(0), T(0)); }
        static constexpr TVector3 Up() { return TVector3(T(0), T(1), T(0)); }
        static constexpr TVector3 Forward() { return TVector3(T(0), T(0), T(1)); }
    };

    //////////////////////////////////////////////////////////////
    // 타입 별칭
    //////////////////////////////////////////////////////////////

    using Vector3F = TVector3<float>;  // float 3차원 벡터
    using Vector3D = TVector3<double>; // double 3차원 벡터
    using Vector3I = TVector3<int32>;  // int32 3차원 벡터
    using Vector3U = TVector3<uint32>; // uint32 3차원 벡터
    using Vector3  = Vector3F;         // 기본 타입은 float

} // namespace TDME