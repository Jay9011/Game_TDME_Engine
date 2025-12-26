#pragma once

#include <Core/CoreTypes.h>
#include <Core/Math/TVector2.h>
#include <Core/Geometry/TRect.h>
#include <vector>
#include "DisplayMode.h"

namespace TDME
{
    struct DisplayInfo
    {
        uint32  Index;       // 디스플레이 인덱스 (0부터)
        wstring Name;        // 디스플레이 이름
        wstring AdapterName; // 디스플레이 어댑터 이름

        Rect Bounds;   // 전체 영역 (가상 데스크톱 좌표)
        Rect WorkArea; // 작업 영역 (작업 표시줄 제외)

        DisplayMode              CurrentMode;    // 현재 디스플레이 모드
        std::vector<DisplayMode> AvailableModes; // 가능한 모드 목록

        bool IsPrimary; // 주 디스플레이 여부
    };
} // namespace TDME