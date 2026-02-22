#pragma once

#include "Core/Math/TVector2.h"
#include "TVector2.h"
#include "TVector3.h"
#include "TQuaternion.h"
#include "TMatrix4x4.h"
#include "Transformations.h"

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
         * @return Matrix 변환된 행렬
         */
        Matrix ToMatrix() const
        {
            // 1. 스케일 행렬
            Matrix scaleMatrix = ScaleMatrix(Scale.X, Scale.Y, Scale.Z);

            // 2. 회전 행렬 (쿼터니언 => 행렬)
            Matrix rotationMatrix = Quaternion::ToMatrix(Rotation);

            // 3. 이동 행렬
            Matrix translationMatrix = TranslationMatrix(Position);

            // SRT 행렬 계산
            return scaleMatrix * rotationMatrix * translationMatrix;
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

        //////////////////////////////////////////////////////////////
        // Getter/Setter
        //////////////////////////////////////////////////////////////

        /**
         * @brief Forward Vector 반환
         * @return Vector3 Forward Vector
         */
        constexpr Vector3 GetForwardVector() const { return Rotation.GetForwardVector(); }

        /**
         * @brief Right Vector 반환
         * @return Vector3 Right Vector
         */
        constexpr Vector3 GetRightVector() const { return Rotation.GetRightVector(); }

        /**
         * @brief Up Vector 반환
         * @return Vector3 Up Vector
         */
        constexpr Vector3 GetUpVector() const { return Rotation.GetUpVector(); }

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
        float GetRotation2D() const
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

    }; // struct Transform
} // namespace TDME