#pragma once

#include "Core/CoreMacros.h"
#include "Core/CoreTypes.h"
#include "MathConstants.h"
#include <cmath>

namespace TDME
{
    /**
     * @brief CRTP(Curiously Recurring Template Pattern) 기반 벡터 연산 템플릿
     * @tparam Derived 파생 클래스 타입
     * @tparam T 벡터 요소 타입
     * @tparam N 벡터 차원
     */
    template <typename Derived, typename T, size_t N>
    struct TVectorOperations
    {
        /**
         * @brief 자기 자신을 Derived 타입으로 캐스팅하여 반환
         * @return Derived 타입의 참조
         */
        constexpr const Derived& Self() const
        {
            return static_cast<const Derived&>(*this);
        }

        /**
         * @brief 자기 자신을 Derived 타입으로 캐스팅하여 반환
         * @return Derived 타입의 참조
         */
        constexpr Derived& Self()
        {
            return static_cast<Derived&>(*this);
        }

        /**
         * @brief 벡터의 길이의 제곱을 반환
         * @return T 벡터의 길이의 제곱값
         */
        constexpr T LengthSquared() const
        {
            T sum = T(0);
            for (size_t i = 0; i < N; i++)
            {
                sum += Self().Data[i] * Self().Data[i];
            }
            return sum;
        }

        /**
         * @brief 실제 길이를 반환
         * @return T 벡터의 길이값
         */
        INLINE T Length() const
        {
            return std::sqrt(LengthSquared());
        }

        /**
         * @brief 정규화된 벡터를 반환
         * @return Derived 정규화된 벡터
         */
        INLINE Derived Normalized() const
        {
            T len = Length();
            if (len < T(Math::SmallNumber))
            {
                return Derived{};
            }

            Derived result;
            for (size_t i = 0; i < N; i++)
            {
                result.Data[i] = Self().Data[i] / len;
            }
            return result;
        }

        /**
         * @brief 두 벡터의 내적을 반환
         * @param other 다른 벡터
         * @return T 두 벡터의 내적값
         */
        constexpr T Dot(const Derived& other) const
        {
            T sum = T(0);
            for (size_t i = 0; i < N; i++)
            {
                sum += Self().Data[i] * other.Data[i];
            }
            return sum;
        }

        //////////////////////////////////////////////////////////////
        // 연산자 오버로딩
        //////////////////////////////////////////////////////////////

        /**
         * @brief 두 벡터의 덧셈을 반환
         * @param other 다른 벡터
         * @return Derived 두 벡터의 덧셈 결과
         */
        constexpr Derived operator+(const Derived& other) const
        {
            Derived result;
            for (size_t i = 0; i < N; i++)
            {
                result.Data[i] = Self().Data[i] + other.Data[i];
            }
            return result;
        }

        /**
         * @brief 두 벡터의 뺄셈을 반환
         * @param other 다른 벡터
         * @return Derived 두 벡터의 뺄셈 결과
         */
        constexpr Derived operator-(const Derived& other) const
        {
            Derived result;
            for (size_t i = 0; i < N; i++)
            {
                result.Data[i] = Self().Data[i] - other.Data[i];
            }
            return result;
        }

        /**
         * @brief 벡터의 스칼라 곱을 반환
         * @param scalar 스칼라값
         * @return Derived 벡터의 스칼라 곱 결과
         */
        constexpr Derived operator*(T scalar) const
        {
            Derived result;
            for (size_t i = 0; i < N; i++)
            {
                result.Data[i] = Self().Data[i] * scalar;
            }
            return result;
        }

        /**
         * @brief 두 벡터의 곱을 반환
         * @param other 다른 벡터
         * @return Derived 두 벡터의 곱 결과
         */
        constexpr Derived operator*(const Derived& other) const
        {
            Derived result;
            for (size_t i = 0; i < N; i++)
            {
                result.Data[i] = Self().Data[i] * other.Data[i];
            }
            return result;
        }

        /**
         * @brief 벡터의 스칼라 나눗셈을 반환
         * @param scalar 스칼라값
         * @return Derived 벡터의 스칼라 나눗셈 결과
         */
        constexpr Derived operator/(T scalar) const
        {
            Derived result;
            for (size_t i = 0; i < N; i++)
            {
                result.Data[i] = Self().Data[i] / scalar;
            }
            return result;
        }

        /**
         * @brief 덧셈 대입 연산자 (+=)
         * @param other 다른 벡터
         * @return const Derived& 덧셈 결과 자기 자긴
         */
        constexpr Derived& operator+=(const Derived& other)
        {
            for (size_t i = 0; i < N; i++)
            {
                Self().Data[i] += other.Data[i];
            }
            return Self();
        }

        /**
         * @brief 뺄셈 대입 연산자 (-=)
         * @param other 다른 벡터
         * @return constexpr Derived& 뺄셈 결과 자기 자신
         */
        constexpr Derived& operator-=(const Derived& other)
        {
            for (size_t i = 0; i < N; i++)
            {
                Self().Data[i] -= other.Data[i];
            }
            return Self();
        }

        /**
         * @brief 스칼라 곱 대입 연산자 (*=)
         * @param scalar 스칼라값
         * @return constexpr Derived& 스칼라 곱 결과 자기 자신
         */
        constexpr Derived& operator*=(T scalar)
        {
            for (size_t i = 0; i < N; i++)
            {
                Self().Data[i] *= scalar;
            }
            return Self();
        }

        /**
         * @brief 벡터 곱 대입 연산자 (*=)
         * @param other 다른 벡터
         * @return constexpr Derived& 벡터 곱 결과 자기 자신
         */
        constexpr Derived& operator*=(const Derived& other)
        {
            for (size_t i = 0; i < N; i++)
            {
                Self().Data[i] *= other.Data[i];
            }
            return Self();
        }

        /**
         * @brief 스칼라 나눗셈 대입 연산자 (/=)
         * @param scalar 스칼라값
         * @return constexpr Derived& 스칼라 나눗셈 결과 자기 자신
         */
        constexpr Derived& operator/=(T scalar)
        {
            for (size_t i = 0; i < N; i++)
            {
                Self().Data[i] /= scalar;
            }
            return Self();
        }

        /**
         * @brief 인덱스 연산자([])
         * @param index 인덱스
         * @return T& 인덱스에 해당하는 요소의 참조
         */
        constexpr T& operator[](size_t index) { return Self().Data[index]; }

        /**
         * @brief 인덱스 연산자([]) - 상수 버전
         * @param index 인덱스
         * @return const T& 인덱스에 해당하는 요소의 상수 참조
         */
        constexpr const T& operator[](size_t index) const { return Self().Data[index]; }

        /**
         * @brief 단항 부정 연산자 (-)
         * @return constexpr Derived 부호 반전
         */
        constexpr Derived operator-() const
        {
            Derived result;
            for (size_t i = 0; i < N; i++)
            {
                result.Data[i] = -Self().Data[i];
            }
            return result;
        }

        /**
         * @brief 비교 연산자(==)
         * @param other 다른 벡터
         * @return bool 두 벡터가 같은지 여부
         */
        constexpr bool operator==(const Derived& other) const
        {
            for (size_t i = 0; i < N; i++)
            {
                if (Self().Data[i] != other.Data[i])
                {
                    return false;
                }
            }
            return true;
        }
    };

} // namespace TDME