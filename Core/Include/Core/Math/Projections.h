#pragma once

#include "Core/CoreMacros.h"
#include "Core/Math/MathConstants.h"
#include "Core/Math/TMatrix4x4.h"

#include <cmath>

namespace TDME
{
    /**
     * @brief 2D 직교 투영 행렬 생성
     * @details 월드 좌표 → NDC (Normalized Device Coordinates) 변환
     * @li NDC X:[left, right] → [-1, 1]
     * @li NDC Y:[bottom, top] → [-1, 1]
     * @li NDC Z:[zNear, zFar] → [0, 1]
     * @tparam T 행렬 요소 타입
     * @param left 왼쪽 테두리
     * @param right 오른쪽 테두리
     * @param bottom 아래쪽 테두리
     * @param top 위쪽 테두리
     * @param zNear 근접 평면
     * @param zFar 원근 평면
     * @return TMatrix4x4<T> 2D 직교 투영 행렬
     */
    template <typename T>
    FORCE_INLINE constexpr TMatrix4x4<T> OrthographicProjection2D(T left, T right, T bottom, T top, T zNear, T zFar)
    {
        // Row Vector, 왼손 좌표계, NDC [0, 1] 사용
        T width  = right - left;
        T height = top - bottom;
        T depth  = zFar - zNear;

        return TMatrix4x4<T>(T(2) / width, 0, 0, 0,
                             0, T(2) / height, 0, 0,
                             0, 0, T(1) / depth, 0,
                             -(right + left) / width, -(top + bottom) / height, -zNear / depth, 1);
    }

    /**
     * @brief 2D 화면 좌표계 직교 투영 행렬 생성
     * @details 좌상단 원점 (0, 0) 사용
     * @note bottom = height, top = 0 으로 전달하여 Y축을 반전.
     * @note 스크린 좌표계(좌상단 원점, Y 아래 증가)를 NDC Y[-1 = 하단, +1 = 상단]으로 매핑.
     * @tparam T 행렬 요소 타입
     * @param width 너비
     * @param height 높이
     * @return TMatrix4x4<T> 2D 직교 투영 행렬
     */
    template <typename T>
    FORCE_INLINE constexpr TMatrix4x4<T> Orthographic2D(T width, T height)
    {
        return OrthographicProjection2D(T(0), width, height, T(0), T(0), T(1));
    }

    /**
     * @brief 2D 화면 좌표계 직교 투영 행렬 생성 (중심 원점 사용)
     * @tparam T 행렬 요소 타입
     * @param width 너비
     * @param height 높이
     * @return TMatrix4x4<T> 2D 직교 투영 행렬
     */
    template <typename T>
    FORCE_INLINE constexpr TMatrix4x4<T> Orthographic2DCentered(T width, T height)
    {
        T halfW = width / T(2);
        T halfH = height / T(2);
        return OrthographicProjection2D(-halfW, halfW, -halfH, halfH, T(0), T(1));
    }

    /**
     * @brief 원근 투영 행렬 생성 (왼손 좌표계)
     * @details 절두체(Frustum)를 NDC로 변환
     * @li NDC X: [-1, 1]
     * @li NDC Y: [-1, 1]
     * @li NDC Z: [0, 1]
     * @tparam T 행렬 요소 타입
     * @param fovY 수직 시야각 (라디안)
     * @param aspectRatio 종횡비 (너비 / 높이)
     * @param zNear 근접 평면 거리 (> 0)
     * @param zFar 원근 평면 거리 (> zNear)
     * @return TMatrix4x4<T> 원근 투영 행렬
     */
    template <typename T>
    FORCE_INLINE constexpr TMatrix4x4<T> PerspectiveFovLH(T fovY, T aspectRatio, T zNear, T zFar)
    {
        // Row Vector, 왼손 좌표계, NDC [0, 1] 사용
        T yScale = T(1) / std::tan(fovY * T(0.5));
        T xScale = yScale / aspectRatio;
        T depth  = zFar - zNear;

        return TMatrix4x4<T>(xScale, 0, 0, 0,
                             0, yScale, 0, 0,
                             0, 0, zFar / depth, 1,
                             0, 0, -zNear * zFar / depth, 0);
    }
} // namespace TDME
