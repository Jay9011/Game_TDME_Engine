#pragma once

#include "Core/CoreMacros.h"
#include "MathConstants.h"

namespace TDME
{
    namespace Math
    {
        /**
         * @brief 값을 [min, max] 범위로 제한
         * @tparam T 자료형 타입
         * @param value 클램핑할 값
         * @param min 최소값
         * @param max 최대값
         * @return FORCE_INLINE constexpr T 클램핑된 값
         */
        template <typename T>
        FORCE_INLINE constexpr T Clamp(T value, T min, T max)
        {
            if (value < min)
                return min;
            if (value > max)
                return max;
            return value;
        }

        /**
         * @brief 선형 보간 (Linear Interpolation)
         * @note start 에서 end 까지 t 값 만큼 보간
         * @tparam T 자료형 타입
         * @param start 시작 값
         * @param end 끝 값
         * @param t 보간 값 ([0, 1] 비율)
         * @return FORCE_INLINE constexpr T 보정된 값
         */
        template <typename T>
        FORCE_INLINE constexpr T Lerp(T start, T end, T t)
        {
            return start + (end - start) * t;
        }

        /**
         * @brief 역 선형 보간 (Inverse Linear Interpolation)
         * @details value가 [start, end] 구간 어디인지 0~1로 반환
         * @tparam T 자료형 타입
         * @param start 시작 값
         * @param end 끝 값
         * @param value 원하는 값 ([start, end] 범위)
         * @return FORCE_INLINE constexpr T 보정된 값 ([0, 1] 범위)
         */
        template <typename T>
        FORCE_INLINE constexpr T InverseLerp(T start, T end, T value)
        {
            if ((end - start) > T(-SmallNumber) && (end - start) < T(SmallNumber))
                return T(0);
            return (value - start) / (end - start);
        }

        /**
         * @brief 두 값이 거의 같은지 비교
         * @tparam T 자료형 타입
         * @param a 비교할 값
         * @param b 비교할 값
         * @param tolerance 허용 오차
         * @return FORCE_INLINE constexpr bool
         */
        template <typename T>
        FORCE_INLINE constexpr bool NearlyEqual(T a, T b, T tolerance = T(KindaSmallNumber))
        {
            T diff = a - b;
            return diff > -tolerance && diff < tolerance;
        }

        /**
         * @brief 도 → 라디안
         * @tparam T 자료형 타입
         * @param degrees 도
         * @return FORCE_INLINE constexpr 라디안
         */
        template <typename T>
        FORCE_INLINE constexpr T DegreesToRadians(T degrees)
        {
            return degrees * T(DegToRad);
        }

        /**
         * @brief 라디안 → 도
         * @tparam T 자료형 타입
         * @param radians 라디안
         * @return FORCE_INLINE constexpr 도
         */
        template <typename T>
        FORCE_INLINE constexpr T RadiansToDegrees(T radians)
        {
            return radians * T(RadToDeg);
        }

        /**
         * @brief 두 값 중 작은 값 반환
         * @tparam T 자료형 타입
         * @param a 비교할 값
         * @param b 비교할 값
         * @return FORCE_INLINE constexpr T 작은 값
         */
        template <typename T>
        FORCE_INLINE constexpr T Min(T a, T b)
        {
            return (a < b) ? a : b;
        }

        /**
         * @brief 두 값 중 큰 값 반환
         * @tparam T 자료형 타입
         * @param a 비교할 값
         * @param b 비교할 값
         * @return FORCE_INLINE constexpr T 큰 값
         */
        template <typename T>
        FORCE_INLINE constexpr T Max(T a, T b)
        {
            return (a > b) ? a : b;
        }
    } // namespace Math
} // namespace TDME
