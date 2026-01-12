#pragma once

#include "Core/CoreMacros.h"
#include "Engine/ApplicationCore/EWindowMode.h"
#include "DisplayMode.h"

namespace TDME
{
    /**
     * @brief 디스플레이 설정 (윈도우/모니터 관련)
     */
    struct DisplaySettings
    {
        DisplayMode Mode;         // 해상도, 주사율, BPP
        EWindowMode WindowMode;   // 창 모드 (Windowed, BorderlessFullscreen, Fullscreen)
        uint32      AdapterIndex; // 사용할 GPU 인덱스

        /**
         * @brief 기본 설정 (1280x720, 60Hz, 32비트, 창 모드, 수직 동기화, GPU 인덱스 0)
         */
        static FORCE_INLINE DisplaySettings Default()
        {
            DisplaySettings settings;
            settings.Mode         = {1280, 720, 60, 32};
            settings.WindowMode   = EWindowMode::Windowed;
            settings.AdapterIndex = 0;
            return settings;
        }

        /**
         * @brief 기본 전체화면 설정 (32비트, GPU 인덱스 0)
         * @param width 너비
         * @param height 높이
         * @param refreshRate 주사율
         */
        static FORCE_INLINE DisplaySettings Fullscreen(uint32 width, uint32 height, uint32 refreshRate = 60)
        {
            DisplaySettings settings;
            settings.Mode         = {width, height, refreshRate, 32};
            settings.WindowMode   = EWindowMode::BorderlessFullscreen;
            settings.AdapterIndex = 0;
            return settings;
        }
    };
} // namespace TDME