#include "pch.h"
#include "Platform_Windows/Time/Win32Timer.h"

#include <algorithm>

namespace TDME
{
    Win32Timer::Win32Timer()
        : m_frequency(), m_startTime(), m_previousTime(), m_currentTime(),
          m_deltaTime(0.0f), m_totalTime(0.0f)
    {
        QueryPerformanceFrequency(&m_frequency); // 하드웨어(메인보드 or CPU)의 초당 Tick Frequency 조회
        Reset();
    }

    void Win32Timer::Reset()
    {
        QueryPerformanceCounter(&m_startTime); // 현재 Tick Counter 조회
        m_previousTime = m_startTime;
        m_currentTime  = m_startTime;
        m_deltaTime    = 0.0f;
        m_totalTime    = 0.0f;
    }

    void Win32Timer::Tick()
    {
        QueryPerformanceCounter(&m_currentTime); // 현재 Tick Counter 조회

        // Delta Time 계산
        float deltaTime = static_cast<float>(m_currentTime.QuadPart - m_previousTime.QuadPart)
                        / static_cast<float>(m_frequency.QuadPart);

        // Clamping: 최대 0.25초
        m_deltaTime = std::min<float>(deltaTime, MAX_DELTA_TIME);

        // Total Time 계산
        m_totalTime = static_cast<float>(m_currentTime.QuadPart - m_startTime.QuadPart)
                    / static_cast<float>(m_frequency.QuadPart);

        // Previous Time 갱신
        m_previousTime = m_currentTime;
    }
} // namespace TDME