#pragma once

#include "Core/CoreMacros.h"
#include "Core/Math/MathConstants.h"
#include "Core/Math/TMatrix4x4.h"

namespace TDME
{
    /**
     * @brief 3D 이동 행렬 생성
     * @tparam T 행렬 요소 타입
     * @param x X 이동 거리
     * @param y Y 이동 거리
     * @param z Z 이동 거리
     * @return TMatrix4x4<T> 3D 이동 행렬
     */
    template <typename T>
    FORCE_INLINE constexpr TMatrix4x4<T> Translation3D(T x, T y, T z)
    {
        return TMatrix4x4<T>(1, 0, 0, 0,
                             0, 1, 0, 0,
                             0, 0, 1, 0,
                             x, y, z, 1);
    }

    /**
     * @brief 3D 이동 행렬 생성 (벡터 사용)
     * @tparam T 행렬 요소 타입
     * @param position 이동 위치
     * @return TMatrix4x4<T> 3D 이동 행렬
     */
    template <typename T>
    FORCE_INLINE constexpr TMatrix4x4<T> Translation3D(const TVector3<T>& position)
    {
        return Translation3D(position.X, position.Y, position.Z);
    }

    /**
     * @brief 3D 스케일 행렬 생성
     * @tparam T 행렬 요소 타입
     * @param x X 스케일 값 (기본값: 1)
     * @param y Y 스케일 값 (기본값: 1)
     * @param z Z 스케일 값 (기본값: 1)
     * @return TMatrix4x4<T> 3D 스케일 행렬
     */
    template <typename T>
    FORCE_INLINE constexpr TMatrix4x4<T> Scale3D(T x = T(1), T y = T(1), T z = T(1))
    {
        return TMatrix4x4<T>(x, 0, 0, 0,
                             0, y, 0, 0,
                             0, 0, z, 0,
                             0, 0, 0, 1);
    }

    /**
     * @brief 3D 점 변환 함수
     * @tparam T 행렬 요소 타입
     * @param point 변환할 점
     * @param matrix 변환 행렬
     * @return TVector3<T> 변환된 점
     */
    template <typename T>
    FORCE_INLINE constexpr TMatrix4x4<T> TransformPoint(const TVector3<T>& point, const TMatrix4x4<T>& matrix)
    {
        // W = 1로 확장하여 변환 후 원근을 나누어 점으로 변환
        T x = point.X * matrix._11 + point.Y * matrix._21 + point.Z * matrix._31 + matrix._41;
        T y = point.X * matrix._12 + point.Y * matrix._22 + point.Z * matrix._32 + matrix._42;
        T z = point.X * matrix._13 + point.Y * matrix._23 + point.Z * matrix._33 + matrix._43;
        T w = point.X * matrix._14 + point.Y * matrix._24 + point.Z * matrix._34 + matrix._44;

        if (w != T(1) && w != T(0))
        {
            return TVector3<T>(x / w, y / w, z / w);
        }
        return TVector3<T>(x, y, z);
    }

    /**
     * @brief 3D 벡터 변환 함수
     * @tparam T 행렬 요소 타입
     * @param vector 변환할 벡터
     * @param matrix 변환 행렬
     * @return TVector3<T> 변환된 벡터
     */
    template <typename T>
    FORCE_INLINE constexpr TVector3<T> TransformVector(const TVector3<T>& vector, const TMatrix4x4<T>& matrix)
    {
        return TVector3<T>(vector.X * matrix._11 + vector.Y * matrix._21 + vector.Z * matrix._31,
                           vector.X * matrix._12 + vector.Y * matrix._22 + vector.Z * matrix._32,
                           vector.X * matrix._13 + vector.Y * matrix._23 + vector.Z * matrix._33);
    }

    // TODO: 추후 3D 구현할 때 나머지 구현 (RotationX, RotationY, RotationZ, LookAt 등...)

} // namespace TDME