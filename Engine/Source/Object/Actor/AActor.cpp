#include "pch.h"
#include "Engine/Object/Actor/AActor.h"

#include <Core/Math/Transform.h>

#include "Engine/Object/Component/GSceneComponent.h"

namespace TDME
{
    static Transform s_defaultTransform; // Root Component가 없을 경우 기본 트랜스폼 (위치, 회전, 스케일 없음)

    AActor::AActor()
        : GameObject(), m_rootComponent(nullptr), m_components()
    {
    }

    AActor::~AActor()
    {
        m_components.clear();
        m_rootComponent = nullptr;
    }

    Transform& AActor::GetTransform()
    {
        if (m_rootComponent)
        {
            return m_rootComponent->GetTransform();
        }
        return s_defaultTransform;
    }

    const Transform& AActor::GetTransform() const
    {
        if (m_rootComponent)
        {
            return static_cast<const GSceneComponent*>(m_rootComponent)->GetTransform();
        }
        return s_defaultTransform;
    }

    Matrix4x4 AActor::GetWorldMatrix() const
    {
        if (m_rootComponent)
        {
            return m_rootComponent->GetWorldMatrix();
        }
        return Matrix4x4::Identity();
    }
} // namespace TDME