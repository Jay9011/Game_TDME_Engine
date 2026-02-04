#pragma once

#include "Engine/Object/GameObject.h"
#include "Engine/Object/ILifecycle.h"
#include "Engine/Object/IUpdatable.h"

namespace TDME
{
    class AActor;

    class GActorComponent : public GameObject, public ILifecycle, public IUpdatable
    {
    public:
        GActorComponent();
        ~GActorComponent() override;

        //////////////////////////////////////////////////////////////
        // 라이프 사이클
        //////////////////////////////////////////////////////////////

        void BeginPlay() override {}
        void Update(float deltaTime) override { (void)deltaTime; }
        void EndPlay() override {}

        //////////////////////////////////////////////////////////////
        // 컴포넌트 관리
        //////////////////////////////////////////////////////////////

        /**
         * @brief 컴포넌트를 Actor에 등록
         * @param owner 소유자 Actor
         */
        void RegisterComponent(AActor* owner);

        /**
         * @brief 컴포넌트 등록 해제
         */
        void UnregisterComponent();

        //////////////////////////////////////////////////////////////
        // Getter / Setter
        //////////////////////////////////////////////////////////////

        /**
         * @brief 소유자 Actor 반환
         * @return AActor* 소유자 Actor
         */
        [[nodiscard]] AActor* GetOwner() const { return m_owner; }

        /**
         * @brief 컴포넌트 활성 여부 반환
         * @return bool 활성 여부
         */
        [[nodiscard]] bool IsActive() const { return m_isActive; }

        /**
         * @brief 컴포넌트 활성 여부 설정
         * @param active 활성 여부
         */
        void SetActive(bool active) { m_isActive = active; }

    protected:
        AActor* m_owner    = nullptr;
        bool    m_isActive = true;
    };
} // namespace TDME