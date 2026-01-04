#pragma once

#include "Core/CoreMacros.h"
#include "TVector3.h"
#include "TVectorOperations.h"

namespace TDME
{
    /**
     * @brief 4차원 벡터 클래스
     * @details TVectorOperations 템플릿에 자기 자신을 파생 클래스로 캐스팅하여 사용합니다.
     * @tparam T 벡터 요소 타입
     */
    template <typename T>
    struct TVector4 : TVectorOperations<TVector4<T>, T, 4>
    {
#pragma warning(push)
#pragma warning(disable : 4201) // 익명 구조체/공용체 사용에 대한 경고 비활성화
        union
        {
            struct
            {
                T X, Y, Z, W;
            };
            struct
            {
                T R, G, B, A;
            };
            T Data[4];
        };
#pragma warning(pop)

        constexpr TVector4() : X(T(0)), Y(T(0)), Z(T(0)), W(T(0)) {}
        constexpr TVector4(T x, T y, T z, T w) : X(x), Y(y), Z(z), W(w) {}

        /**
         * @brief 스칼라값으로 초기화
         * @param scalar 스칼라값
         * @return TVector4 스칼라값으로 초기화된 벡터
         */
        explicit constexpr TVector4(T scalar) : X(scalar), Y(scalar), Z(scalar), W(scalar) {}

        /**
         * @brief 3차원 벡터에서 W 값을 추가하여 4차원 벡터로 변환
         * @param v3 3차원 벡터
         * @param w W 값 (기본값: 0)
         * @return TVector4 4차원 벡터
         */
        FORCE_INLINE constexpr TVector4(const TVector3<T>& v3, T w = T(0)) : X(v3.X), Y(v3.Y), Z(v3.Z), W(w) {}

        /**
         * @brief XY 성분을 TVector2로 반환
         * @return TVector2<T> XY 성분으로 구성된 2차원 벡터
         */
        FORCE_INLINE constexpr TVector2<T> XY() const
        {
            return TVector2<T>(X, Y);
        }

        /**
         * @brief XYZ 성분을 TVector3로 반환
         * @return TVector3<T> XYZ 성분으로 구성된 3차원 벡터
         */
        FORCE_INLINE constexpr TVector3<T> XYZ() const
        {
            return TVector3<T>(X, Y, Z);
        }

        /**
         * @brief 4차원 벡터를 3차원 벡터로 변환
         * @details W 값으로 나누어 원근을 나눈 3차원 벡터로 변환
         * @return TVector3<T> 3차원 벡터
         */
        FORCE_INLINE constexpr TVector3<T> ToCartesian() const { return TVector3<T>(X / W, Y / W, Z / W); }

        /**
         * @brief 3차원 벡터를 4차원 점 벡터로 반환
         * @param v 3차원 벡터
         * @return TVector4 4차원 점 벡터
         */
        static FORCE_INLINE constexpr TVector4 Point(const TVector3<T>& v) { return TVector4(v, T(1)); }

        /**
         * @brief 3차원 벡터를 4차원 벡터로 반환
         * @param v 3차원 벡터
         * @return TVector4 4차원 벡터
         */
        static FORCE_INLINE constexpr TVector4 Vector(const TVector3<T>& v) { return TVector4(v, T(0)); }

        //////////////////////////////////////////////////////////////
        // 미리 정의된 벡터
        //////////////////////////////////////////////////////////////

        static constexpr TVector4 Zero() { return TVector4(T(0), T(0), T(0), T(0)); }
        static constexpr TVector4 One() { return TVector4(T(1), T(1), T(1), T(1)); }
        static constexpr TVector4 UnitX() { return TVector4(T(1), T(0), T(0), T(0)); }
        static constexpr TVector4 UnitY() { return TVector4(T(0), T(1), T(0), T(0)); }
        static constexpr TVector4 UnitZ() { return TVector4(T(0), T(0), T(1), T(0)); }
        static constexpr TVector4 UnitW() { return TVector4(T(0), T(0), T(0), T(1)); }
    };

    //////////////////////////////////////////////////////////////
    // 타입 별칭
    //////////////////////////////////////////////////////////////

    using Vector4F = TVector4<float>;  // float 4차원 벡터
    using Vector4D = TVector4<double>; // double 4차원 벡터
    using Vector4I = TVector4<int32>;  // int32 4차원 벡터
    using Vector4U = TVector4<uint32>; // uint32 4차원 벡터
    using Vector4  = Vector4F;         // 기본 타입은 float

} // namespace TDME