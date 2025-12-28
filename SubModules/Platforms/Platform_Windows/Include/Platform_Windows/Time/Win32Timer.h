#pragma once

#include <Engine/Time/ITimer.h>
#include <Windows.h>
#include <winnt.h>

namespace TDME
{
    class Win32Timer : public ITimer
    {
    public:
        Win32Timer();
        ~Win32Timer() override = default;

        /**
         * @brief 타이머 초기화
         */
        void Reset() override;

        /**
         * @brief 매 프레임 호출 (Delta Time 계산)
         * @note 매 프레임 호출 시 현재 시간과 이전 시간의 차이를 계산하여 Delta Time을 반환
         */
        void Tick() override;

        //////////////////////////////////////////////////////////////
        // Getter / Setter
        //////////////////////////////////////////////////////////////

        /** @brief 이전 프레임과 현재 프레임의 시간 차이를 반환 (초 단위) */
        float GetDeltaTime() const override { return m_deltaTime; }

        /** @brief 타이머가 시작된 이후의 총 시간을 반환 (초 단위) */
        float GetTotalTime() const override { return m_totalTime; }

    private:
        LARGE_INTEGER m_frequency;    // 초당 Tick 수
        LARGE_INTEGER m_startTime;    // 타이머 시작 시간
        LARGE_INTEGER m_previousTime; // 이전 프레임 시간
        LARGE_INTEGER m_currentTime;  // 현재 프레임 시간

        float m_deltaTime; // 프레임 간 시간 차이 (초 단위)
        float m_totalTime; // 타이머가 시작된 이후의 총 시간 (초 단위)

        static constexpr float MAX_DELTA_TIME = 0.25f; // 최대 Delta Time (0.25초)
    };
} // namespace TDME