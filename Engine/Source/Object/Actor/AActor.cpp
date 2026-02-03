#include "pch.h"
#include "Engine/Object/Actor/AActor.h"

#include <algorithm>

namespace TDME
{
    AActor::AActor()
        : GameObject(), m_transform(), m_parent(nullptr), m_children()
    {
    }

    AActor::~AActor()
    {
        DetachFromParent(); // 부모로부터 분리

        // 자식즐의 부모 참조 제거
        for (AActor* child : m_children)
        {
            if (child)
                child->m_parent = nullptr;
        }
        m_children.clear();
    }

    Matrix4x4 AActor::GetWorldMatrix() const
    {
        Matrix4x4 localMatrix = m_transform.ToMatrix();

        if (m_parent)
        {
            // Loacl Matrix x Parent World Matrix (Parent의 World Transform으로 계산된 World Matrix가 재귀적으로 호출되어 적용됨)
            return localMatrix * m_parent->GetWorldMatrix();
        }

        return localMatrix;
    }

    void AActor::AttachToActor(AActor* parent)
    {
        if (m_parent == parent)
            return;

        DetachFromParent(); // 기존 부모로부터 분리

        // 새 부모에 부착
        m_parent = parent;
        if (m_parent)
        {
            m_parent->m_children.push_back(this);
        }
    }

    void AActor::DetachFromParent()
    {
        if (m_parent)
        {
            std::vector<AActor*>& parentChildren = m_parent->m_children;
            parentChildren.erase(std::remove(parentChildren.begin(), parentChildren.end(), this), parentChildren.end());
            m_parent = nullptr;
        }
    }
} // namespace TDME