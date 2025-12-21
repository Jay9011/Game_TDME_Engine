#pragma once

#include <Core/CoreTypes.h>
#include <Core/Math/TVector2.h>

namespace TDME
{
    /**
     * @brief 2차원 사각형 클래스
     * @tparam T 요소 타입
     */
    template <typename T>
    struct TRect
    {
        T X, Y;
        T Width, Height;

        //////////////////////////////////////////////////////////////
        // 생성자
        //////////////////////////////////////////////////////////////

        constexpr TRect() : X(T(0)), Y(T(0)), Width(T(0)), Height(T(0)) {}

        constexpr TRect(T x, T y, T width, T height)
            : X(x), Y(y), Width(width), Height(height) {}

        constexpr TRect(const TVector2<T>& position, const TVector2<T>& size)
            : X(position.X), Y(position.Y), Width(size.X), Height(size.Y) {}

        //////////////////////////////////////////////////////////////
        // Getter / Setter
        //////////////////////////////////////////////////////////////

        /**
         * @brief 왼쪽
         * @return T 왼쪽 위치
         */
        constexpr T Left() const { return X; }

        /**
         * @brief 오른쪽
         * @return T 오른쪽 위치
         */
        constexpr T Right() const { return X + Width; }

        /**
         * @brief 상단
         * @return T 상단 위치
         */
        constexpr T Top() const { return Y; }

        /**
         * @brief 하단
         * @return T 하단 위치
         */
        constexpr T Bottom() const { return Y + Height; }

        /**
         * @brief 위치 반환
         * @return TVector2<T> 위치
         */
        constexpr TVector2<T> GetPosition() const
        {
            return TVector2<T>(X, Y);
        }

        /**
         * @brief 크기 반환
         * @return TVector2<T> 크기
         */
        constexpr TVector2<T> GetSize() const
        {
            return TVector2<T>(Width, Height);
        }

        /**
         * @brief 중앙 좌표 반환
         * @return TVector2<T> 중심점
         */
        constexpr TVector2<T> GetCenter() const
        {
            return TVector2<T>(X + Width / T(2), Y + Height / T(2));
        }

        /**
         * @brief 넓이 반환
         * @return T 넓이
         */
        constexpr T GetArea() const
        {
            return Width * Height;
        }

        /**
         * @brief 유효한 사각형인지 확인 (크기가 양수)
         * @return bool 유효한 사각형인지 여부
         */
        constexpr bool IsValid() const
        {
            return Width > T(0) && Height > T(0);
        }

        //////////////////////////////////////////////////////////////
        // 충돌 관련
        //////////////////////////////////////////////////////////////

        /**
         * @brief 점이 사각형 내부에 있는지 확인
         * @param point 검사할 점
         */
        constexpr bool Contains(const TVector2<T>& point) const
        {
            return point.X >= X && point.X <= Right()
                && point.Y >= Y && point.Y <= Bottom();
        }

        /**
         * @brief 다른 사각형이 완전히 내부에 있는지 확인
         * @param other 검사할 사각형
         */
        constexpr bool Contains(const TRect& other) const
        {
            return other.X >= X && other.Right() <= Right()
                && other.Y >= Y && other.Bottom() <= Bottom();
        }

        /**
         * @brief 다른 사각형과 겹치는지 확인
         * @param other 검사할 사각형
         */
        constexpr bool Intersects(const TRect& other) const
        {
            return !(Right() < other.X || other.Right() < X
                     || Bottom() < other.Y || other.Bottom() < Y);
        }

        //////////////////////////////////////////////////////////////
        // 변환
        //////////////////////////////////////////////////////////////

        /**
         * @brief 사각형 이동
         * @param offset 이동량
         * @return TRect 이동된 사각형
         */
        constexpr TRect Translated(const TVector2<T>& offset) const
        {
            return TRect(X + offset.X, Y + offset.Y, Width, Height);
        }

        /**
         * @brief 사각형 확장 (모든 방향으로)
         * @param amount 확장량
         * @return TRect 확장된 사각형
         */
        constexpr TRect Expanded(T amount) const
        {
            return TRect(X - amount, Y - amount, Width + amount * T(2), Height + amount * T(2));
        }

        /**
         * @brief 두 사각형의 합집합 (둘을 포함하는 최소 사각형)
         * @param other 다른 사각형
         * @return TRect 합집합 사각형
         */
        constexpr TRect Union(const TRect& other) const
        {
            T minX = X < other.X ? X : other.X;
            T minY = Y < other.Y ? Y : other.Y;
            T maxX = Right() > other.Right() ? Right() : other.Right();
            T maxY = Bottom() > other.Bottom() ? Bottom() : other.Bottom();
            return TRect(minX, minY, maxX - minX, maxY - minY);
        }

        /**
         * @brief 두 사각형의 교집합
         * @param other 다른 사각형
         * @return TRect 교집합 사각형 (겹치지 않으면 크기가 0 또는 음수)
         */
        constexpr TRect Intersection(const TRect& other) const
        {
            T minX = X > other.X ? X : other.X;
            T minY = Y > other.Y ? Y : other.Y;
            T maxX = Right() < other.Right() ? Right() : other.Right();
            T maxY = Bottom() < other.Bottom() ? Bottom() : other.Bottom();
            return TRect(minX, minY, maxX - minX, maxY - minY);
        }

        //////////////////////////////////////////////////////////////
        // 연산자 오버로딩
        //////////////////////////////////////////////////////////////

        /**
         * @brief 두 사각형이 같은지 확인
         * @param other 다른 사각형
         * @return bool 두 사각형이 같은지 여부
         */
        constexpr bool operator==(const TRect& other) const
        {
            return X == other.X && Y == other.Y
                && Width == other.Width && Height == other.Height;
        }

        /**
         * @brief 두 사각형이 다른지 확인
         * @param other 다른 사각형
         * @return bool 두 사각형이 다른지 여부
         */
        constexpr bool operator!=(const TRect& other) const
        {
            return !(*this == other);
        }

        //////////////////////////////////////////////////////////////
        // 미리 정의된 Rect
        //////////////////////////////////////////////////////////////

        static constexpr TRect Zero() { return TRect(T(0), T(0), T(0), T(0)); }
    };

    //////////////////////////////////////////////////////////////
    // 타입 별칭
    //////////////////////////////////////////////////////////////

    using RectF = TRect<float>;  // float 사각형
    using RectD = TRect<double>; // double 사각형
    using RectI = TRect<int32>;  // int32 사각형
    using RectU = TRect<uint32>; // uint32 사각형
    using Rect  = RectF;         // 기본 타입은 float

} // namespace TDME
