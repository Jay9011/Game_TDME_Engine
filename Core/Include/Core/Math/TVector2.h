#pragma once

#include "Core/CoreMacros.h"
#include "TVectorOperations.h"

namespace TDME
{
    /**
     * @brief 2차원 벡터 클래스
     * @details TVectorOperations 템플릿에 자기 자신을 파생 클래스로 캐스팅하여 사용합니다.
     * @tparam T 벡터 요소 타입
     */
    template <typename T>
    struct TVector2 : TVectorOperations<TVector2<T>, T, 2>
    {
#pragma warning(push)
#pragma warning(disable : 4201) // 익명 구조체/공용체 사용에 대한 경고 비활성화
        union
        {
            struct
            {
                T X, Y;
            };
            struct
            {
                T U, V;
            };
            T Data[2];
        };
#pragma warning(pop)

        constexpr TVector2() : X(T(0)), Y(T(0)) {}
        constexpr TVector2(T x, T y) : X(x), Y(y) {}

        /**
         * @brief 스칼라값으로 초기화
         * @param scalar 스칼라값
         * @return TVector2 스칼라값으로 초기화된 벡터
         */
        explicit constexpr TVector2(T scalar) : X(scalar), Y(scalar) {}

        /**
         * @brief 2D 외적 계산 (스칼라 결과)
         * @param other 다른 벡터
         * @return T 외적값 (스칼라)
         */
        constexpr T Cross(const TVector2& other) const
        {
            return X * other.Y - Y * other.X;
        }

        /**
         * @brief 수직 벡터
         * @return TVector2 수직 벡터
         */
        constexpr TVector2 Perpendicular() const
        {
            return TVector2(-Y, X);
        }

        //////////////////////////////////////////////////////////////
        // 미리 정의된 벡터
        //////////////////////////////////////////////////////////////

        static constexpr TVector2 Zero() { return TVector2(T(0), T(0)); }
        static constexpr TVector2 One() { return TVector2(T(1), T(1)); }
        static constexpr TVector2 UnitX() { return TVector2(T(1), T(0)); }
        static constexpr TVector2 UnitY() { return TVector2(T(0), T(1)); }
    };

    //////////////////////////////////////////////////////////////
    // 타입 별칭
    //////////////////////////////////////////////////////////////
    // Vector 별칭

    using Vector2F = TVector2<float>;  // float 2차원 벡터
    using Vector2D = TVector2<double>; // double 2차원 벡터
    using Vector2I = TVector2<int32>;  // int32 2차원 벡터
    using Vector2U = TVector2<uint32>; // uint32 2차원 벡터
    using Vector2  = Vector2F;         // 기본 타입은 float

    // Point 별칭

    using PointF  = TVector2<float>;
    using PointI  = TVector2<int32>;
    using PointLL = TVector2<int64>;
    using Point   = PointI;

} // namespace TDME