#include "pch.h"
#include "Game/Object/Actor/APlanet.h"

#include <Core/Math/TVector2.h>
#include <Core/Math/Transform.h>
#include <Engine/Object/Component/GSceneComponent.h>
#include <Engine/Renderer/Shape/Shape2DRenderer.h>

namespace TDME
{
    APlanet::APlanet()
        : AActor()
    {
        m_orbit       = AddComponent<GSceneComponent>(true); // Root Component로 설정
        m_orbitOffset = AddComponent<GSceneComponent>();
        m_body        = AddComponent<GSceneComponent>();

        m_orbitOffset->AttachToComponent(m_orbit);
        m_body->AttachToComponent(m_orbitOffset); // Body를 OrbitPivot에 부착
    }

    void APlanet::Update(float deltaTime)
    {
        // 공전 (OrbitPivot 회전)
        if (m_orbitSpeed != 0.0f)
        {
            Transform& orbitTransform = m_orbit->GetTransform();
            orbitTransform.SetRotation2D(orbitTransform.GetRotation2D() + m_orbitSpeed * deltaTime); // 궤도 속도만큼 회전
        }

        // 자전 (Body 회전)
        if (m_spinSpeed != 0.0f)
        {
            Transform& bodyTransform = m_body->GetTransform();
            bodyTransform.SetRotation2D(bodyTransform.GetRotation2D() + m_spinSpeed * deltaTime); // 자전 속도만큼 회전
        }
    }

    void APlanet::Render(Shape2DRenderer& renderer)
    {
        renderer.DrawCircle(m_body->GetWorldMatrix(), m_bodyRadius, m_color, 5);
    }

    void APlanet::OrbitAround(APlanet* parent)
    {
        if (parent)
        {
            m_orbit->AttachToComponent(parent->GetOrbitOffsetComponent()); // Root Component 를 Parent의 Root Component에 부착
        }
    }

    void APlanet::SetOrbitRadius(float radius)
    {
        m_orbitOffset->GetTransform().SetPosition2D(Vector2(radius, 0.0f));
    }
} // namespace TDME