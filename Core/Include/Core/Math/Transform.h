#pragma once

#include "Core/Math/TVector2.h"
#include "TVector2.h"
#include "TVector3.h"
#include "TQuaternion.h"
#include "TMatrix4x4.h"
#include "Detail/TMatrix4x4.Transform3D.h"

#include <cmath>

namespace TDME
{
    /**
     * @brief Transform 구조체
     * @details 위치, 회전, 스케일 정보를 가지고 있는 구조체
     */
    struct Transform
    {
        Vector3    Position = Vector3::Zero();
        Quaternion Rotation = Quaternion::Identity();
        Vector3    Scale    = Vector3::One();

        constexpr Transform() = default;
        constexpr Transform(const Vector3& position, const Quaternion& rotation, const Vector3& scale) : Position(position), Rotation(rotation), Scale(scale) {}

        /**
         * @brief Transform을 행렬로 변환
         * @details SRT (Scale * Rotation * Translation) 행렬 계산
         * @return Matrix4 변환된 행렬
         */
        Matrix4 ToMatrix() const
        {
            // 1. 스케일 행렬
            Matrix4 scaleMatrix = Scale3D(Scale.X, Scale.Y, Scale.Z);

            // 2. 회전 행렬 (쿼터니언 => 행렬)
            Matrix4 rotationMatrix = QuaternionToMatrix(Rotation);

            // 3. 이동 행렬
            Matrix4 translationMatrix = Translation3D(Position);

            // SRT 행렬 계산
            return scaleMatrix * rotationMatrix * translationMatrix;
        }

        //////////////////////////////////////////////////////////////
        // Getter/Setter
        //////////////////////////////////////////////////////////////

        /**
         * @brief 2D 위치 반환
         * @return Vector2 2D 위치
         */
        constexpr Vector2 GetPosition2D() const
        {
            return Vector2(Position.X, Position.Y);
        }

        /**
         * @brief 2D 위치 설정
         * @param position 2D 위치
         */
        constexpr void SetPosition2D(const Vector2& position)
        {
            Position.X = position.X;
            Position.Y = position.Y;
        }

        /**
         * @brief 2D 회전 각도 반환
         * @return float 2D 회전 각도 (라디안)
         */
        constexpr float GetRotation2D() const
        {
            // 쿼터니언에서 Z축 회전 각도 추출
            return 2.0f * std::atan2(Rotation.Z, Rotation.W);
        }

        /**
         * @brief 2D 회전 설정
         * @param radians 회전 각도 (라디안)
         */
        constexpr void SetRotation2D(float radians)
        {
            Rotation = Quaternion::FromRotationZ(radians);
        }

        /**
         * @brief 2D 스케일 반환
         * @return Vector2 2D 스케일
         */
        constexpr Vector2 GetScale2D() const
        {
            return Vector2(Scale.X, Scale.Y);
        }

        /**
         * @brief 2D 스케일 설정
         * @param scale 2D 스케일
         */
        constexpr void SetScale2D(const Vector2& scale)
        {
            Scale.X = scale.X;
            Scale.Y = scale.Y;
        }

        //////////////////////////////////////////////////////////////
        // 정적 함수
        //////////////////////////////////////////////////////////////

        /**
         * @brief 2D 값으로 Transform을 생성
         * @param position 위치
         * @param rotation 회전
         * @param scale 스케일
         * @return Transform 생성된 Transform
         */
        static constexpr Transform From2D(const Vector2& position, float rotation, const Vector2& scale = Vector2::One())
        {
            return Transform(Vector3(position.X, position.Y, 0), Quaternion::FromRotationZ(rotation), Vector3(scale.X, scale.Y, 1));
        }

    private:
        static Matrix4 QuaternionToMatrix(const Quaternion& quaternion)
        {
            float xx = quaternion.X * quaternion.X, yy = quaternion.Y * quaternion.Y, zz = quaternion.Z * quaternion.Z;
            float xy = quaternion.X * quaternion.Y, xz = quaternion.X * quaternion.Z, yz = quaternion.Y * quaternion.Z;
            float wx = quaternion.W * quaternion.X, wy = quaternion.W * quaternion.Y, wz = quaternion.W * quaternion.Z;

            return Matrix4(
                1.0f - 2.0f * (yy + zz), 2.0f * (xy + wz), 2.0f * (xz - wy), 0.0f, // X
                2.0f * (xy - wz), 1.0f - 2.0f * (xx + zz), 2.0f * (yz + wx), 0.0f, // Y
                2.0f * (xz + wy), 2.0f * (yz - wx), 1.0f - 2.0f * (xx + yy), 0.0f, // Z
                0.0f, 0.0f, 0.0f, 1.0f                                             // W
            );
        }

    }; // struct Transform
} // namespace TDME