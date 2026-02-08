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
         * @brief 트랜스폼 상수(const) 반환 (읽기 전용)
         */
        [[nodiscard]] const Transform& GetTransform() const { return m_transform; }

        /**
         * @brief 트랜스폼 설정
         * @param transform 트랜스폼
         */
        void SetTransform(const Transform& transform);

        /**
         * @brief 트랜스폼 더티 플래그 설정 (부모 컴포넌트의 World Matrix 계산 필요 시 호출)
         */
        void SetTransformDirty();

        /**
         * @brief 위치 설정
         * @param position 위치
         */
        void SetPosition(const Vector3& position);

        /**
         * @brief 회전 설정
         * @param rotation 회전
         */
        void SetRotation(const Quaternion& rotation);

        /**
         * @brief 스케일 설정
         * @param scale 스케일
         */
        void SetScale(const Vector3& scale);

        /**
         * @brief World Matrix 반환
         * @details Dirty Flag가 설정되어 있으면 부모 컴포넌트의 World Matrix를 재귀적으로 계산하여 반환
         * @return const Matrix& 월드 Matrix
         */
        [[nodiscard]] const Matrix& GetWorldMatrix() const;

    protected:
        Transform m_transform;

        GSceneComponent*              m_parent = nullptr;
        std::vector<GSceneComponent*> m_children;

    private:
        mutable Matrix m_cachedWorldMatrix = Matrix::Identity();
        mutable bool   m_isDirty           = true;

        /**
         * @brief 자손 컴포넌트들에 Dirty Flag 를 Top-Down 방식으로 전파
         */
        void PropagateDirtyFlagToChildren();

        /**
         * @brief World Matrix 재계산
         */
        void RecalculateWorldMatrix() const;
    };
} // namespace TDME