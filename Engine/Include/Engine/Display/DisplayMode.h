#pragma once

#include <Core/CoreTypes.h>

namespace TDME
{
    /**
     * @brief 디스플레이 모드 구조체
     * @details 너비, 높이, 주사율, 등의 정보를 포함하는 구조체
     */
    struct DisplayMode
    {
        uint32 Width;        // 너비
        uint32 Height;       // 높이
        uint32 RefreshRate;  // Hz (0이면 기본값 사용)
        uint32 BitsPerPixel; // 보통 32

        bool operator==(const DisplayMode& other) const
        {
            return Width == other.Width
                && Height == other.Height
                && RefreshRate == other.RefreshRate;
        }
    };
} // namespace TDME
