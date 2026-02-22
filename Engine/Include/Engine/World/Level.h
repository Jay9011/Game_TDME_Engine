#pragma once

#include <memory>
#include <vector>

namespace TDME
{
    class AActor;

    /**
     * @brief Level: 월드 내의 맵 혹은 여러 맵에 지속되는 게임 플레이 영역.
     * @details Actor를 소유하고 일괄 Update/Render를 수행하는 컨테이너.
     */
    class Level
    {
    public:
        Level();
        ~Level();

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
        // Actor 관리
        //////////////////////////////////////////////////////////////

        /**
         * @brief Actor를 생성하고 Level에 등록한 후 바로 BeginPlay를 호출
         * @tparam T 생성할 AActor 파생 클래스
         * @tparam Args 생성자에 전달할 인자들
         * @param args 생성자에 전달할 인자들
         * @return T* 생성된 Actor의 포인터 (소유권은 Level이 가짐)
         */
        template <typename T, typename... Args>
        T* SpawnActor(Args&&... args)
        {
            static_assert(std::is_base_of_v<AActor, T>, "T must be derived from AActor");

            // 1. Actor 생성
            auto actor = std::make_unique<T>(std::forward<Args>(args)...);
            T*   ptr   = actor.get();

            // 2. Actor 소유권 이전
            m_actors.push_back(std::move(actor));

            // 3. BeginPlay 호출
            ptr->BeginPlay();
            return ptr;
        }

        /**
         * @brief Actor 지연 삭제 예약 (PendingDestroy)
         * @details 즉시 삭제하지 않고 다음 Update 에서 FlushPendingDestroy 에서 실제 삭제
         * @note 즉시 삭제할 경우 이터레이터 무효화, 멀티 스레드, 다중 접근 등 문제가 발생할 수 있음
         * @param actor 파괴할 Actor
         */
        void DestroyActor(AActor* actor);

    private:
        /**
         * @brief 지연 삭제 대기중인 Actor들을 실제로 삭제
         */
        void FlushPendingDestroy();

        std::vector<std::unique_ptr<AActor>> m_actors;
        std::vector<AActor*>                 m_pendingDestroy;
    };
} // namespace TDME
