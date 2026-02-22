#include "pch.h"
#include "Game/Object/Actor/APlanet.h"

#include <Core/Math/Transform.h>
#include <Core/Math/TQuaternion.h>
#include <Core/Math/TVector3.h>
#include <Engine/Object/Component/GSceneComponent.h>
#include <Engine/Renderer/Shape/Shape3DRenderer.h>

namespace TDME
{
    APlanet::APlanet()
        : AActor()
    {
        m_orbit       = AddComponent<GSceneComponent>(true); // 공전 공간(Root Component) 설정
        m_orbitOffset = AddComponent<GSceneComponent>();     // 공전 반경 추가
        m_body        = AddComponent<GSceneComponent>();     // 자전

        m_orbitOffset->AttachToComponent(m_orbit);
        m_body->AttachToComponent(m_orbitOffset); // Body를 OrbitPivot에 부착
    }

    void APlanet::Update(float deltaTime)
    {
        // 공전 (OrbitPivot 회전)
        if (m_orbitSpeed != 0.0f)
        {
            const Transform& orbitTransform = m_orbit->GetTransform();
            m_orbit->SetRotation(Quaternion::FromRotationZ(orbitTransform.GetRotation2D() + m_orbitSpeed * deltaTime)); // 궤도 속도만큼 회전
        }

        // 자전 (Body 회전)
        if (m_spinSpeed != 0.0f)
        {
            const Transform& bodyTransform = m_body->GetTransform();
            m_body->SetRotation(Quaternion::FromRotationZ(bodyTransform.GetRotation2D() + m_spinSpeed * deltaTime)); // 자전 속도만큼 회전
        }
    }

    void APlanet::Render()
    {
        if (!m_renderer)
            return;

        if (m_texture) // 텍스처가 있으면 텍스처 기반으로 렌더링
        {
            m_renderer->DrawTexturedSphere(m_body->GetWorldMatrix(), m_bodyRadius, m_texture);
        }
        else // (폴백) 텍스처가 없으면 색상 기반으로 렌더링
        {
            m_renderer->DrawSphere(m_body->GetWorldMatrix(), m_bodyRadius, m_color);
        }
    }

    void APlanet::OrbitAround(APlanet* parent)
    {
        if (parent)
        {
            m_orbit->AttachToComponent(parent->GetOrbitOffsetComponent()); // 공전 컴포넌트를 부모의 공전 Offset 컴포넌트에 부착
        }
    }

    void APlanet::SetOrbitRadius(float radius)
    {
        m_orbitOffset->SetPosition(Vector3(radius, 0.0f, 0.0f));
    }
} // namespace TDME