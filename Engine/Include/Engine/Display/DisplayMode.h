#pragma once

#include "Core/CoreTypes.h"
namespace TDME
{
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
