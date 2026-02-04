#pragma once

namespace TDME
{
    /**
     * @brief 라이프 사이클 인터페이스
     * @details 게임 오브젝트의 시작/종료 시점에 호출되는 인터페이스
     */
    class ILifecycle
    {
    public:
        virtual ~ILifecycle() = default;

        /** @brief 게임 시작/스폰 시 호출 */
        virtual void BeginPlay() = 0;

        /** @brief 게임 종료/파괴 시 호출 */
        virtual void EndPlay() = 0;
    };
} // namespace TDME