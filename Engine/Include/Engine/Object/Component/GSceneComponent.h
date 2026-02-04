#pragma once

#include <Core/Math/Transform.h>
#include <Core/Math/TMatrix4x4.h>

#include "Engine/Object/Component/GActorComponent.h"

#include <vector>

namespace TDME
{
    /**
     * @brief SceneComponent 클래스
     * @details Scene에 배치 가능한 (Transform 계층 구조를 가지는) 컴포넌트
     * @see TDME::GActorComponent
     */
    class GSceneComponent : public GActorComponent
    {
    public:
        GSceneComponent();
        ~GSceneComponent() override;

        //////////////////////////////////////////////////////////////
        // 컴포넌트 관리
        //////////////////////////////////////////////////////////////

        /**
         * @brief 컴포넌트를 다른 컴포넌트에 부착
         * @param parent 부모 컴포넌트
         */
        void AttachToComponent(GSceneComponent* parent);

        /**
         * @brief 컴포넌트를 부모 컴포넌트에서 분리
         */
        void DetachFromParent();

        //////////////////////////////////////////////////////////////
        // Getter / Setter
        //////////////////////////////////////////////////////////////

        /**
         * @brief 부모 컴포넌트 반환
         */
        [[nodiscard]] GSceneComponent* GetParentComponent() const { return m_parent; }

        /**
         * @brief 자식 컴포넌트 목록 반환
         */
        [[nodiscard]] const std::vector<GSceneComponent*>& GetChildrenComponents() const { return m_children; }

        /**
         * @brief 트랜스폼 반환
         */
        [[nodiscard]] Transform& GetTransform() { return m_transform; }

        /**
         * @brief 트랜스폼 상수(const) 반환
         */
        [[nodiscard]] const Transform& GetTransform() const { return m_transform; }

        /**
         * @brief 트랜스폼 설정
         * @param transform 트랜스폼
         */
        void SetTransform(const Transform& transform) { m_transform = transform; }

        /**
         * @brief World Matrix 반환
         * @details 부모 컴포넌트의 World Matrix를 재귀적으로 계산하여 반환
         * @return Matrix4x4 월드 Matrix
         */
        [[nodiscard]] Matrix4x4 GetWorldMatrix() const;

    protected:
        Transform m_transform;

        GSceneComponent*              m_parent = nullptr;
        std::vector<GSceneComponent*> m_children;
    };
} // namespace TDME