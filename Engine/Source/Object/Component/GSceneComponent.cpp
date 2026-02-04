#include "pch.h"
#include "Engine/Object/Component/GSceneComponent.h"

namespace TDME
{
    GSceneComponent::GSceneComponent()
        : GActorComponent(), m_transform(), m_parent(nullptr), m_children()
    {
    }

    GSceneComponent::~GSceneComponent()
    {
        DetachFromParent();

        // 자식들의 부모 참조 제거
        for (GSceneComponent* child : m_children)
        {
            if (child)
                child->m_parent = nullptr;
        }
        m_children.clear();
    }

    Matrix4x4 GSceneComponent::GetWorldMatrix() const
    {
        Matrix4x4 localMatrix = m_transform.ToMatrix();

        if (m_parent)
        {
            // Loacl Matrix x Parent World Matrix (Parent의 World Transform으로 계산된 World Matrix가 재귀적으로 호출되어 적용됨)
            return localMatrix * m_parent->GetWorldMatrix();
        }

        return localMatrix;
    }

    void GSceneComponent::AttachToComponent(GSceneComponent* parent)
    {
        if (m_parent == parent)
            return;

        DetachFromParent();

        m_parent = parent;
        if (m_parent)
        {
            m_parent->m_children.push_back(this);
        }
    }

    void GSceneComponent::DetachFromParent()
    {
        if (m_parent)
        {
            std::vector<GSceneComponent*>& parentChildren = m_parent->m_children;
            parentChildren.erase(std::remove(parentChildren.begin(), parentChildren.end(), this), parentChildren.end());
            m_parent = nullptr;
        }
    }
} // namespace TDME