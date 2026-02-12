#pragma once

#include "Core/CoreMacros.h"
#include "Core/Math/MathConstants.h"
#include "Core/Math/TMatrix4x4.h"
#include "Core/Math/TVector2.h"
#include "Core/Math/TVector3.h"

namespace TDME
{
    /**
     * @brief 2D 이동 행렬 생성 (Z = 0 인 평면)
     * @param x X 이동 거리
     * @param y Y 이동 거리
     * @return TMatrix4x4<T> 2D 이동 행렬
     */
    template <typename T>
    FORCE_INLINE constexpr TMatrix4x4<T> Translation2D(T x, T y)
    {
        return TMatrix4x4<T>(1, 0, 0, 0,
                             0, 1, 0, 0,
                             0, 0, 1, 0,
                             x, y, 0, 1);
    }

    /**
     * @brief 2D 이동 행렬 생성 (2차원 벡터 사용)
     * @tparam T 행렬 요소 타입
     * @param position 이동 위치
     * @return TMatrix4x4<T> 2D 이동 행렬
     */
    template <typename T>
    FORCE_INLINE constexpr TMatrix4x4<T> Translation2D(const TVector2<T>& position)
    {
        return Translation2D(position.X, position.Y);
    }

    /**
     * @brief 2D 이동 행렬 생성 (3차원 벡터 사용)
     * @tparam T 행렬 요소 타입
     * @param position 이동 위치
     * @return TMatrix4x4<T> 2D 이동 행렬
     */
    template <typename T>
    FORCE_INLINE constexpr TMatrix4x4<T> Translation2D(const TVector3<T>& position)
    {
        return Translation2D(position.X, position.Y);
    }

    /**
     * @brief 2D 회전 행렬 생성
     * @details Z 축 중심, 왼손 좌표계 사용
     * @tparam T 행렬 요소 타입
     * @param radian 회전 각도
     * @return TMatrix4x4<T> 2D 회전 행렬
     */
    template <typename T>
    FORCE_INLINE constexpr TMatrix4x4<T> Rotation2D(T radian)
    {
        T c = std::cos(radian);
        T s = std::sin(radian);

        return TMatrix4x4<T>(c, s, 0, 0,
                             -s, c, 0, 0,
                             0, 0, 1, 0,
                             0, 0, 0, 1);
    }

    /**
     * @brief 2D 스케일 행렬 생성
     * @tparam T 행렬 요소 타입
     * @param x X 스케일 값 (기본값: 1)
     * @param y Y 스케일 값 (기본값: 1)
     * @return TMatrix4x4<T> 2D 스케일 행렬
     */
    template <typename T>
    FORCE_INLINE constexpr TMatrix4x4<T> Scale2D(T x = T(1), T y = T(1))
    {
        return TMatrix4x4<T>(x, 0, 0, 0,
                             0, y, 0, 0,
                             0, 0, 1, 0,
                             0, 0, 0, 1);
    }

    /**
     * @brief 2D 스케일 행렬 생성 (스칼라 값 사용)
     * @tparam T 행렬 요소 타입
     * @param scale 스케일 값
     * @return TMatrix4x4<T> 2D 스케일 행렬
     */
    template <typename T>
    FORCE_INLINE constexpr TMatrix4x4<T> Scale2D(T scale)
    {
        return Scale2D(scale, scale);
    }

    /**
     * @brief 2D 스케일 행렬 생성 (2차원 벡터 사용)
     * @tparam T 행렬 요소 타입
     * @param scale 스케일 값
     * @return TMatrix4x4<T> 2D 스케일 행렬
     */
    template <typename T>
    FORCE_INLINE constexpr TMatrix4x4<T> Scale2D(const TVector2<T>& scale)
    {
        return Scale2D(scale.X, scale.Y);
    }

    /**
     * @brief 2D 스케일 행렬 생성 (3차원 벡터 사용)
     * @tparam T 행렬 요소 타입
     * @param scale 스케일 값
     * @return TMatrix4x4<T> 2D 스케일 행렬
     */
    template <typename T>
    FORCE_INLINE constexpr TMatrix4x4<T> Scale2D(const TVector3<T>& scale)
    {
        return Scale2D(scale.X, scale.Y);
    }

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

    //////////////////////////////////////////////////////////////
    // 벡터 변환 함수
    //////////////////////////////////////////////////////////////

    /**
     * @brief 2D 점 변환 함수
     * @tparam T 행렬 요소 타입
     * @param point 변환할 점
     * @param matrix 변환 행렬
     * @return TVector2<T> 변환된 점
     */
    template <typename T>
    FORCE_INLINE constexpr TVector2<T> TransformPoint2D(const TVector2<T>& point, const TMatrix4x4<T>& matrix)
    {
        T x = point.X * matrix._11 + point.Y * matrix._21 + matrix._41;
        T y = point.X * matrix._12 + point.Y * matrix._22 + matrix._42;
        T w = point.X * matrix._14 + point.Y * matrix._24 + matrix._44;

        if (w != T(1) && w != T(0))
        {
            return TVector2<T>(x / w, y / w);
        }
        return TVector2<T>(x, y);
    }

    /**
     * @brief 2D 벡터 변환 함수
     * @tparam T 행렬 요소 타입
     * @param vector 변환할 벡터
     * @param matrix 변환 행렬
     * @return TVector2<T> 변환된 벡터
     */
    template <typename T>
    FORCE_INLINE constexpr TVector2<T> TransformVector2D(const TVector2<T>& vector, const TMatrix4x4<T>& matrix)
    {
        return TVector2<T>(vector.X * matrix._11 + vector.Y * matrix._21,
                           vector.X * matrix._12 + vector.Y * matrix._22);
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

    //////////////////////////////////////////////////////////////
    // 뷰 행렬 생성
    //////////////////////////////////////////////////////////////

    /**
     * @brief 왼손 좌표계 LookAt 뷰 행렬 생성
     * @details 카메라 위치, 바라보는 점, 위쪽 방향으로 뷰 행렬을 생성 (Row-vector(v × M) 기준)
     * @tparam T 행렬 요소 타입
     * @param eye 카메라 위치
     * @param target 바라보는 점
     * @param up 위쪽 방향
     * @return TMatrix4x4<T> 뷰 행렬
     */
    template <typename T>
    INLINE constexpr TMatrix4x4<T> LookAtLH(const TVector3<T>& eye, const TVector3<T>& target, const TVector3<T>& up)
    {
        TVector3<T> zAxis = (target - eye).Normalized();  // 카메라 전방
        TVector3<T> xAxis = up.Cross(zAxis).Normalized(); // 카메라 오른쪽
        TVector3<T> yAxis = zAxis.Cross(xAxis);           // 카메라 위쪽

        return TMatrix4x4<T>(
            xAxis.X, yAxis.X, zAxis.X, T(0),
            xAxis.Y, yAxis.Y, zAxis.Y, T(0),
            xAxis.Z, yAxis.Z, zAxis.Z, T(0),
            -xAxis.Dot(eye), -yAxis.Dot(eye), -zAxis.Dot(eye), T(1));
    }

    // TODO: 추후 3D 구현할 때 나머지 구현 (RotationX, RotationY, RotationZ 등...)

} // namespace TDME