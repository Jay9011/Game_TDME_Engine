#pragma once

#include "EWindowMode.h"

namespace TDME
{
    struct WindowDesc
    {
        EWindowMode WindowMode = EWindowMode::Windowed; // 창 모드

        uint32 DisplayIndex = 0; // 디스플레이 인덱스

        string Title = "TDME 창 제목"; // 창 제목

        uint32 Width  = 1280; // 창 너비
        uint32 Height = 720;  // 창 높이

        int32 PositionX = -1; // 창 위치 X (기본값: 시스템 기본값)
        int32 PositionY = -1; // 창 위치 Y (기본값: 시스템 기본값)

        bool bResizable      = true; // 창 크기 조절 가능 여부
        bool bShowOnCreation = true; // 창 생성 시 표시 여부

        //////////////////////////////////////////////////////////////
        // 전체화면 관련
        //////////////////////////////////////////////////////////////

        uint32 FullscreenWidth       = 0; // 전체화면 너비
        uint32 FullscreenHeight      = 0; // 전체화면 높이
        uint32 FullscreenRefreshRate = 0; // 전체화면 주사율
    };
} // namespace TDME