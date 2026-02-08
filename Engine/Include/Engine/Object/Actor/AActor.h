#pragma once

#include <Core/Math/Transform.h>
#include <Core/Math/TMatrix4x4.h>

#include "Engine/Object/GameObject.h"
#include "Engine/Object/ILifecycle.h"
#include "Engine/Object/IUpdatable.h"

#include <memory>
#include <vector>

namespace TDME
{
    class GActorComponent;
    class GSceneComponent;

    /**
     * @brief Actor 클래스
     * @details 월드에 배치 가능한 게임 오브젝트의 베이스 클래스
     * @see TDME::GameObject, TDME::ILifecycle, TDME::IUpdatable
     */
    class AActor : public GameObject, public ILifecycle, public IUpdatable
    {
    public:
        AActor();
        ~AActor() override;

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
         * @brief 컴포넌트 추가
         * @tparam T 컴포넌트 타입 (GActorComponent를 상속받은 클래스)
         * @return T* 추가된 컴포넌트 포인터
         */
        template <typename T>
        T* AddComponent(bool isRoot = false)
        {
            static_assert(std::is_base_of_v<GActorComponent, T>, "T must derive from GActorComponent");
            auto component = std::make_unique<T>();

            T* ptr = component.get();
            ptr->RegisterComponent(this);

            if constexpr (std::is_base_of_v<GSceneComponent, T>) // T가 GSceneComponent를 상속받고 isRoot가 true인 경우, Root Component로 설정
            {
                if (isRoot)
                    m_rootComponent = ptr;
            }

            m_components.push_back(std::move(component));
            return ptr;
        }

        /**
         * @brief 컴포넌트 찾아서 반환
         * @tparam T 컴포넌트 타입
         * @return T* 찾은 컴포넌트 포인터 (없으면 nullptr)
         */
        template <typename T>
        T* GetComponent() const
        {
            for (const auto& component : m_components)
            {
                if (T* casted = dynamic_cast<T*>(component.get()))
                {
                    return casted;
                }
            }
            return nullptr;
        }

        //////////////////////////////////////////////////////////////
        // Getter / Setter
        //////////////////////////////////////////////////////////////

        /**
         * @brief Root Component 반환
         */
        [[nodiscard]] GSceneComponent* GetRootComponent() const { return m_rootComponent; }

        /**
         * @brief Root Component 설정
         * @param component Root Component
         */
        void SetRootComponent(GSceneComponent* component) { m_rootComponent = component; }

        /**
         * @brief Transform 반환
         * @details Root Component의 Transform을 반환
         */
        [[nodiscard]] Transform& GetTransform();

        /**
         * @brief Transform 상수(const) 반환
         * @details Root Component의 Transform을 반환
         */
        [[nodiscard]] const Transform& GetTransform() const;

        /**
         * @brief World Matrix 반환
         * @details Root Component의 World Matrix를 반환
         */
        [[nodiscard]] Matrix GetWorldMatrix() const;

    protected:
        GSceneComponent*                              m_rootComponent = nullptr;
        std::vector<std::unique_ptr<GActorComponent>> m_components;

    }; // class AActor
} // namespace TDME