#pragma once

#include "Level.h"
#include <memory>

namespace TDME
{
    /**
     * @brief World: 게임 월드
     * @details Level 을 소유하고 게임 루프를 관리.
     */
    class World
    {
    public:
        World();
        ~World();

        //////////////////////////////////////////////////////////////
        // Game Loop
        //////////////////////////////////////////////////////////////

        /**
         * @brief 매 프레임 호출
         * @param deltaTime 이전 프레임과의 시간 차이 (초)
         */
        void Update(float deltaTime);

        /**
         * @brief 매 프레임 렌더링 호출
         */
        void Render();

        //////////////////////////////////////////////////////////////
        // Level 관리
        //////////////////////////////////////////////////////////////

        [[nodiscard]] Level* GetPersistentLevel() const { return m_persistentLevel.get(); }

        //////////////////////////////////////////////////////////////
        // Actor 관리 (Level 에 위임)
        //////////////////////////////////////////////////////////////

        /**
         * @brief Actor 생성 (Level 에 생성)
         * @tparam T 생성할 AActor 파생 클래스
         * @tparam Args 생성자에 전달할 인자들
         * @param args 생성자에 전달할 인자들
         * @return T* 생성된 Actor의 포인터 (소유권은 Level이 가짐)
         */
        template <typename T, typename... Args>
        T* SpawnActor(Args&&... args)
        {
            return m_persistentLevel->SpawnActor<T>(std::forward<Args>(args)...);
        }

        /**
         * @brief Actor 파괴 (Level 에 위임)
         * @param actor 파괴할 Actor
         */
        void DestroyActor(AActor* actor);

    private:
        std::unique_ptr<Level> m_persistentLevel;
    };
} // namespace TDME