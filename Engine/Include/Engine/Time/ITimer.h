#pragma once

namespace TDME
{
    /**
     * @brief 타이머 인터페이스
     * @details 게임 플레이를 위한 시간 측정
     */
    class ITimer
    {
    public:
        virtual ~ITimer() = default;

        /**
         * @brief 타이머 초기화
         */
        virtual void Reset() = 0;

        /**
         * @brief 매 프레임 호출 (Delta Time 계산)
         * @note 매 프레임 호출 시 현재 시간과 이전 시간의 차이를 계산하여 Delta Time을 반환
         */
        virtual void Tick() = 0;

        //////////////////////////////////////////////////////////////
        // Getter / Setter
        //////////////////////////////////////////////////////////////

        /** @brief 이전 프레임과 현재 프레임의 시간 차이를 반환 (초 단위) */
        virtual float GetDeltaTime() const = 0;
        /** @brief 타이머가 시작된 이후의 총 시간을 반환 (초 단위) */
        virtual float GetTotalTime() const = 0;
    };
} // namespace TDME