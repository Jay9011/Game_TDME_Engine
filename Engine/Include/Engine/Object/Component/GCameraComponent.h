#pragma once

#include <Core/Math/MathConstants.h>
#include <Core/Math/Projections.h>

#include "Engine/Object/Component/GSceneComponent.h"

namespace TDME
{
    /**
     * @brief 카메라 컴포넌트
     * @details GSceneComponent를 상속받아 Transform(위치/회전)을 사용하는 카메라 컴포넌트.
     * @note View Matrix 는 WorldMatrix의 역행렬, 투영 행렬은 내부 파라미터로 생성.
     * @see TDME::GSceneComponent
     */
    class GCameraComponent : public GSceneComponent
    {
    public:
        GCameraComponent();
        ~GCameraComponent() override = default;

        //////////////////////////////////////////////////////////////
        // 6 DOF 이동 및 회전 (로컬 좌표 기준)
        //////////////////////////////////////////////////////////////

        /**
         * @brief 전/후방 이동 (로컬 Z축)
         * @param distance 이동 거리 (양수 = 전진, 음수 = 후진)
         */
        void MoveForward(float distance);

        /**
         * @brief 좌/우 이동 (로컬 X축)
         * @param distance 이동 거리 (양수 = 오른쪽, 음수 = 왼쪽)
         */
        void MoveRight(float distance);

        /**
         * @brief 상/하 이동 (로컬 Y축)
         * @param distance 이동 거리 (양수 = 위, 음수 = 아래)
         */
        void MoveUp(float distance);

        /**
         * @brief Yaw 회전 (로컬 Y축)
         * @param radian 회전 각도 (라디안)
         */
        void RotateYaw(float radian);

        /**
         * @brief Pitch 회전 (로컬 X축)
         * @param radian 회전 각도 (라디안)
         */
        void RotatePitch(float radian);

        /**
         * @brief Roll 회전 (로컬 Z축)
         * @param radian 회전 각도 (라디안)
         */
        void RotateRoll(float radian);

        //////////////////////////////////////////////////////////////
        // 행렬
        //////////////////////////////////////////////////////////////

        /**
         * @brief 뷰 행렬 반환
         * @details WorldMatrix의 역행렬 = View 행렬
         * @return Matrix 뷰 행렬
         */
        [[nodiscard]] Matrix GetViewMatrix() const
        {
            return GetWorldMatrix().Inverse();
        }

        /**
         * @brief 투영 행렬 반환
         * @return Matrix 투영 행렬
         */
        [[nodiscard]] Matrix GetProjectionMatrix() const
        {
            return PerspectiveFovLH(m_fovY, m_aspectRatio, m_nearZ, m_farZ);
        }

        //////////////////////////////////////////////////////////////
        // Getter/Setter
        //////////////////////////////////////////////////////////////

        /**
         * @brief 원근 투영 파라미터 설정
         * @param fovY 시야각 (라디안)
         * @param aspectRatio 종횡비 (너비/높이)
         * @param nearZ 근접 평면
         * @param farZ 원근 평면
         */
        void SetPerspective(float fovY, float aspectRatio, float nearZ, float farZ)
        {
            m_fovY        = fovY;
            m_aspectRatio = aspectRatio;
            m_nearZ       = nearZ;
            m_farZ        = farZ;
        }

    private:
        float m_fovY        = Math::Pi / 3.0f; // 시야각 (60도)
        float m_aspectRatio = 16.0f / 9.0f;    // 화면 비율 (16:9)
        float m_nearZ       = 1.0f;            // 근거리
        float m_farZ        = 1000.0f;         // 원거리
    };

} // namespace TDME