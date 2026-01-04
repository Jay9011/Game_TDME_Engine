#pragma once

#include "Core/CoreTypes.h"
#include "Core/Math/TVector2.h"
#include "Core/Math/TVector3.h"
#include "Core/Math/TVector4.h"

namespace TDME
{
    /**
     * @brief 4x4 행렬 클래스
     * @details DirectX 9 행렬 표기법 사용 (Unreal 표기법)
     * @tparam T 행렬 요소 타입
     */
    template <typename T>
    struct TMatrix4x4
    {
#pragma warning(push)
#pragma warning(disable : 4201) // 익명 구조체/공용체 사용에 대한 경고 비활성화
        union
        {
            struct
            {
                T _11, _12, _13, _14;
                T _21, _22, _23, _24;
                T _31, _32, _33, _34;
                T _41, _42, _43, _44;
            };
            struct
            {
                T Xx, Xy, Xz, Xw; // Right Vector
                T Yx, Yy, Yz, Yw; // Up Vector
                T Zx, Zy, Zz, Zw; // Forward Vector
                T Tx, Ty, Tz, Tw; // 이동 벡터
            };
            T M[4][4];
            T Data[16]; // GPU 전달용 1D 배열
        };
#pragma warning(pop)

        constexpr TMatrix4x4() : Data{} {}

        constexpr TMatrix4x4(T m11, T m12, T m13, T m14,
                             T m21, T m22, T m23, T m24,
                             T m31, T m32, T m33, T m34,
                             T m41, T m42, T m43, T m44)
            : _11(m11), _12(m12), _13(m13), _14(m14),
              _21(m21), _22(m22), _23(m23), _24(m24),
              _31(m31), _32(m32), _33(m33), _34(m34),
              _41(m41), _42(m42), _43(m43), _44(m44) {}

        /**
         * @brief 행렬의 전치행렬을 반환
         * @return TMatrix4x4 행렬의 전치행렬
         */
        constexpr TMatrix4x4 Transposed() const
        {
            return TMatrix4x4(
                _11, _21, _31, _41,
                _12, _22, _32, _42,
                _13, _23, _33, _43,
                _14, _24, _34, _44);
        }

        /**
         * @brief 행렬의 이동 벡터를 반환
         * @return TVector3<T> 행렬의 이동 벡터
         */
        constexpr TVector3<T> GetTranslationVector() const
        {
            return TVector3<T>(Tx, Ty, Tz);
        }

        /**
         * @brief 행렬의 이동 벡터를 설정
         * @param translation 이동 벡터
         */
        constexpr void SetTranslationVector(const TVector2<T>& translation)
        {
            Tx = translation.X;
            Ty = translation.Y;
        }

        /**
         * @brief 행렬의 이동 벡터를 설정
         * @param translation 이동 벡터
         */
        constexpr void SetTranslationVector(const TVector3<T>& translation)
        {
            Tx = translation.X;
            Ty = translation.Y;
            Tz = translation.Z;
        }

        /**
         * @brief 행렬식 반환 (역행렬 존재 여부 확인용)
         * @details 행렬식이 0이 아니면 역행렬 존재
         * @return T 행렬식
         */
        constexpr T Determinant() const
        {
            return _11 * Minor3x3(1, 2, 3, 1, 2, 3)
                 - _12 * Minor3x3(1, 2, 3, 0, 2, 3)
                 + _13 * Minor3x3(1, 2, 3, 0, 1, 3)
                 - _14 * Minor3x3(1, 2, 3, 0, 1, 2);
        }

        /**
         * @brief 역행렬 반환
         * @return TMatrix4x4 역행렬
         */
        constexpr TMatrix4x4 Inverse() const
        {
            T det    = Determinant();
            T invDet = T(1) / det;

            TMatrix4x4 result;

            // 수반 행렬의 전치/행렬식
            result._11 = +Minor3x3(1, 2, 3, 1, 2, 3) * invDet;
            result._12 = -Minor3x3(0, 2, 3, 1, 2, 3) * invDet;
            result._13 = +Minor3x3(0, 1, 3, 1, 2, 3) * invDet;
            result._14 = -Minor3x3(0, 1, 2, 1, 2, 3) * invDet;

            result._21 = -Minor3x3(1, 2, 3, 0, 2, 3) * invDet;
            result._22 = +Minor3x3(0, 2, 3, 0, 2, 3) * invDet;
            result._23 = -Minor3x3(0, 1, 3, 0, 2, 3) * invDet;
            result._24 = +Minor3x3(0, 1, 2, 0, 2, 3) * invDet;

            result._31 = +Minor3x3(1, 2, 3, 0, 1, 3) * invDet;
            result._32 = -Minor3x3(0, 2, 3, 0, 1, 3) * invDet;
            result._33 = +Minor3x3(0, 1, 3, 0, 1, 3) * invDet;
            result._34 = -Minor3x3(0, 1, 2, 0, 1, 3) * invDet;

            result._41 = -Minor3x3(1, 2, 3, 0, 1, 2) * invDet;
            result._42 = +Minor3x3(0, 2, 3, 0, 1, 2) * invDet;
            result._43 = -Minor3x3(0, 1, 3, 0, 1, 2) * invDet;
            result._44 = +Minor3x3(0, 1, 2, 0, 1, 2) * invDet;

            return result;
        }

        //////////////////////////////////////////////////////////////
        // 연산자 오버로딩
        //////////////////////////////////////////////////////////////

        /**
         * @brief 행렬의 덧셈을 반환
         * @param other 다른 행렬
         * @return TMatrix4x4 행렬의 덧셈 결과
         */
        constexpr TMatrix4x4 operator+(const TMatrix4x4& other) const
        {
            TMatrix4x4 result;
            for (size_t i = 0; i < 16; i++)
            {
                result.Data[i] = Data[i] + other.Data[i];
            }
            return result;
        }

        /**
         * @brief 행렬의 덧셈을 계산하여 자기 자신에 저장
         * @param other 다른 행렬
         * @return TMatrix4x4& 자기 자신의 참조
         */
        TMatrix4x4& operator+=(const TMatrix4x4& other)
        {
            *this = *this + other;
            return *this;
        }

        /**
         * @brief 행렬의 스칼라 곱을 반환
         * @param scalar 스칼라값
         * @return TMatrix4x4 행렬의 스칼라 곱 결과
         */
        constexpr TMatrix4x4 operator*(T scalar) const
        {
            TMatrix4x4 result;
            for (size_t i = 0; i < 16; i++)
            {
                result.Data[i] = Data[i] * scalar;
            }
            return result;
        }

        /**
         * @brief 행렬의 스칼라 곱을 계산하여 자기 자신에 저장
         * @param scalar 스칼라값
         * @return TMatrix4x4& 자기 자신의 참조
         */
        TMatrix4x4& operator*=(T scalar)
        {
            *this = *this * scalar;
            return *this;
        }

        /**
         * @brief 두 행렬의 곱을 반환
         * @param other 다른 행렬
         * @return TMatrix4x4 두 행렬의 곱 결과
         */
        constexpr TMatrix4x4 operator*(const TMatrix4x4& other) const
        {
            TMatrix4x4 result;
            for (size_t row = 0; row < 4; row++)
            {
                for (size_t col = 0; col < 4; col++)
                {
                    result.M[row][col] = M[row][0] * other.M[0][col]
                                       + M[row][1] * other.M[1][col]
                                       + M[row][2] * other.M[2][col]
                                       + M[row][3] * other.M[3][col];
                }
            }
            return result;
        }

        /**
         * @brief 두 행렬의 곱을 계산하여 자기 자신에 저장
         * @param other 다른 행렬
         * @return TMatrix4x4& 자기 자신의 참조
         */
        TMatrix4x4& operator*=(const TMatrix4x4& other)
        {
            *this = *this * other;
            return *this;
        }

        /**
         * @brief 두 행렬이 같은지 확인
         * @param other 다른 행렬
         * @return bool 두 행렬이 같은지 여부
         */
        constexpr bool operator==(const TMatrix4x4& other) const
        {
            for (size_t i = 0; i < 16; i++)
            {
                if (Data[i] != other.Data[i])
                {
                    return false;
                }
            }
            return true;
        }

        /**
         * @brief 두 행렬이 다른지 확인
         * @param other 다른 행렬
         * @return bool 두 행렬이 다른지 여부
         */
        constexpr bool operator!=(const TMatrix4x4& other) const
        {
            return !(*this == other);
        }

        /**
         * @brief 행렬의 행을 반환
         * @param row 행 인덱스
         * @return T* 행렬의 행 참조
         */
        T* operator[](size_t row) { return M[row]; }

        /**
         * @brief 행렬의 행을 반환
         * @param row 행 인덱스
         * @return const T* 행렬의 행 상수 참조
         */
        const T* operator[](size_t row) const { return M[row]; }

        //////////////////////////////////////////////////////////////
        // 미리 정의된 행렬
        //////////////////////////////////////////////////////////////

        static constexpr TMatrix4x4 Zero() { return TMatrix4x4(); }
        static constexpr TMatrix4x4 Identity() { return TMatrix4x4(T(1), T(0), T(0), T(0),
                                                                   T(0), T(1), T(0), T(0),
                                                                   T(0), T(0), T(1), T(0),
                                                                   T(0), T(0), T(0), T(1)); }

    private:
        /**
         * @brief 3x3 부분행렬의 행렬식을 반환
         * @return T 3x3 부분행렬의 행렬식
         */
        constexpr T Minor3x3(size_t row0, size_t row1, size_t row2, size_t col0, size_t col1, size_t col2) const
        {
            return M[row0][col0] * (M[row1][col1] * M[row2][col2] - M[row1][col2] * M[row2][col1])
                 - M[row0][col1] * (M[row1][col0] * M[row2][col2] - M[row1][col2] * M[row2][col0])
                 + M[row0][col2] * (M[row1][col0] * M[row2][col1] - M[row1][col1] * M[row2][col0]);
        }
    };

    //////////////////////////////////////////////////////////////
    // 타입 별칭
    //////////////////////////////////////////////////////////////

    using Matrix4x4F = TMatrix4x4<float>;  // float 4x4 행렬
    using Matrix4x4D = TMatrix4x4<double>; // double 4x4 행렬
    using Matrix4x4  = Matrix4x4F;         // 기본 타입은 float
    using Matrix4    = Matrix4x4;          // 4x4 행렬 별칭

} // namespace TDME
