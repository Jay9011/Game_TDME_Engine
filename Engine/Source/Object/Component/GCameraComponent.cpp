#include "pch.h"
#include "Engine/Object/Component/GCameraComponent.h"

#include <Core/Math/TQuaternion.h>
#include <Core/Math/TVector3.h>

namespace TDME
{
    GCameraComponent::GCameraComponent()
        : GSceneComponent()
    {
    }

    void GCameraComponent::MoveForward(float distance)
    {
        Vector3 forward = m_transform.GetForwardVector();
        SetPosition(m_transform.Position + forward * distance);
    }

    void GCameraComponent::MoveRight(float distance)
    {
        Vector3 right = m_transform.GetRightVector();
        SetPosition(m_transform.Position + right * distance);
    }

    void GCameraComponent::MoveUp(float distance)
    {
        Vector3 up = m_transform.GetUpVector();
        SetPosition(m_transform.Position + up * distance);
    }

    void GCameraComponent::RotateYaw(float radian)
    {
        Quaternion yawRotation = Quaternion::FromAxisAngle(m_transform.GetUpVector(), radian);
        SetRotation((m_transform.Rotation * yawRotation).Normalized());
    }

    void GCameraComponent::RotatePitch(float radian)
    {
        Quaternion pitchRotation = Quaternion::FromAxisAngle(m_transform.GetRightVector(), radian);
        SetRotation((m_transform.Rotation * pitchRotation).Normalized());
    }

    void GCameraComponent::RotateRoll(float radian)
    {
        Quaternion rollRotation = Quaternion::FromAxisAngle(m_transform.GetForwardVector(), radian);
        SetRotation((m_transform.Rotation * rollRotation).Normalized());
    }

} // namespace TDME