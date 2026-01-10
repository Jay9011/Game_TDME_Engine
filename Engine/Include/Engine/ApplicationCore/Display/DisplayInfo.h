#pragma once

#include <Core/CoreTypes.h>
#include <Core/Math/TVector2.h>
#include <Core/Geometry/TRect.h>

#include "DisplayMode.h"

#include <vector>

namespace TDME
{
    /**
     * @brief 하드웨어 디스플레이(모니터) 정보 구조체
     */
    struct DisplayInfo
    {
        uint32 Index;       // 디스플레이 인덱스 (0부터)
        string Name;        // 디스플레이 이름
        string AdapterName; // 디스플레이 어댑터 이름

        Rect Bounds;   // 전체 영역 (가상 데스크톱 좌표)
        Rect WorkArea; // 작업 영역 (작업 표시줄 제외)

        DisplayMode              CurrentMode;    // 현재 디스플레이 모드
        std::vector<DisplayMode> AvailableModes; // 가능한 모드 목록

        bool IsPrimary; // 주 디스플레이 여부
    };
} // namespace TDME