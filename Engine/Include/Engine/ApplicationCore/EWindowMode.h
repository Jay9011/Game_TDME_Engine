#pragma once

#include <Core/CoreTypes.h>

namespace TDME
{
    /**
     * @brief 창 모드 열거형
     */
    enum class EWindowMode : int8
    {
        Windowed,
        BorderlessFullscreen,
        Fullscreen,
    };
} // namespace TDME
