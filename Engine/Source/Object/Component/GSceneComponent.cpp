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

        SetTransformDirty(); // 부모 컴포넌트 변경 시 World Matrix 캐시 무효화
    }

    void GSceneComponent::DetachFromParent()
    {
        if (m_parent)
        {
            std::vector<GSceneComponent*>& parentChildren = m_parent->m_children;
            parentChildren.erase(std::remove(parentChildren.begin(), parentChildren.end(), this), parentChildren.end());
            m_parent = nullptr;

            SetTransformDirty(); // 부모에서 분리되었으므로 World Matrix 캐시 무효화
        }
    }

    //////////////////////////////////////////////////////////////
    // Getter / Setter
    //////////////////////////////////////////////////////////////

    void GSceneComponent::SetTransform(const Transform& transform)
    {
        m_transform = transform;
        SetTransformDirty();
    }

    void GSceneComponent::SetTransformDirty()
    {
        if (!m_isDirty)
        {
            m_isDirty = true;
            PropagateDirtyFlagToChildren();
        }
    }

    void GSceneComponent::SetPosition(const Vector3& position)
    {
        m_transform.Position = position;
        SetTransformDirty();
    }

    void GSceneComponent::SetRotation(const Quaternion& rotation)
    {
        m_transform.Rotation = rotation;
        SetTransformDirty();
    }

    void GSceneComponent::SetScale(const Vector3& scale)
    {
        m_transform.Scale = scale;
        SetTransformDirty();
    }

    const Matrix& GSceneComponent::GetWorldMatrix() const
    {
        if (m_isDirty)
        {
            RecalculateWorldMatrix();
        }
        return m_cachedWorldMatrix;
    }

    //////////////////////////////////////////////////////////////
    // Private Functions
    //////////////////////////////////////////////////////////////

    void GSceneComponent::PropagateDirtyFlagToChildren()
    {
        for (GSceneComponent* child : m_children)
        {
            if (child && !child->m_isDirty)
            {
                child->m_isDirty = true;
                child->PropagateDirtyFlagToChildren();
            }
        }
    }

    void GSceneComponent::RecalculateWorldMatrix() const
    {
        Matrix localMatrix = m_transform.ToMatrix();

        if (m_parent)
        {
            // Local Matrix x Parent World Matrix (부모가 Dirty Flag면 부모도 재계산 후 캐시 반환)
            m_cachedWorldMatrix = localMatrix * m_parent->GetWorldMatrix();
        }
        else
        {
            m_cachedWorldMatrix = localMatrix;
        }

        m_isDirty = false;
    }

} // namespace TDME