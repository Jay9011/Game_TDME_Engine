#pragma once

#include <Core/Math/Transform.h>
#include <Core/Math/TMatrix4x4.h>

#include "Engine/Object/GameObject.h"

#include <vector>

namespace TDME
{
    /**
     * @brief Actor 클래스
     * @details 월드에 배치 가능한 게임 오브젝트의 베이스 클래스
     * @see TDME::GameObject
     */
    class AActor : public GameObject
    {
    public:
        AActor();
        ~AActor() override;

        //////////////////////////////////////////////////////////////
        // 라이프 사이클
        //////////////////////////////////////////////////////////////

        /** @brief 게임 시작/스폰시 호출 */
        virtual void BeginPlay() {}

        /** @brief 매 프레임 호출 */
        virtual void Update(float deltaTime) { (void)deltaTime; }

        /** @brief 게임 종료/스폰시 호출 */
        virtual void EndPlay() {}

        //////////////////////////////////////////////////////////////
        // 부모/자식 관리
        //////////////////////////////////////////////////////////////

        /**
         * @brief 부모 Actor에 부착
         * @param parent 부모 Actor
         */
        void AttachToActor(AActor* parent);

        /**
         * @brief 부모 Actor에서 분리
         */
        void DetachFromParent();

        //////////////////////////////////////////////////////////////
        // Getter / Setter
        //////////////////////////////////////////////////////////////

        /**
         * @brief 부모 액터 반환
         * @return AActor* 부모 액터
         */
        [[nodiscard]] AActor* GetParent() const { return m_parent; }

        /**
         * @brief 자식 액터 목록 반환
         * @return const std::vector<AActor*>& 자식 액터 목록
         */
        [[nodiscard]] const std::vector<AActor*>& GetChildren() const { return m_children; }

        /**
         * @brief 트랜스폼 반환
         * @return Transform& 트랜스폼
         */
        [[nodiscard]] Transform& GetTransform() { return m_transform; }

        /**
         * @brief 트랜스폼 상수 반환
         * @return const Transform& 트랜스폼
         */
        [[nodiscard]] const Transform& GetTransform() const { return m_transform; }

        /**
         * @brief 트랜스폼 설정
         * @param transform 트랜스폼
         */
        void SetTransform(const Transform& transform) { m_transform = transform; }

        /**
         * @brief 월드 Matrix 반환
         * @details 부모 액터의 월드 Matrix를 재귀적으로 계산하여 반환
         * @return Matrix4x4 월드 Matrix
         */
        [[nodiscard]] Matrix4x4 GetWorldMatrix() const;

    protected:
        Transform m_transform;

        AActor*              m_parent = nullptr;
        std::vector<AActor*> m_children;

    }; // class AActor
} // namespace TDME