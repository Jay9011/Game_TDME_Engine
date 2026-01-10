#pragma once

#include <Core/CoreTypes.h>

namespace TDME
{
    //////////////////////////////////////////////////////////////
    // Key 타입 분류
    //////////////////////////////////////////////////////////////

    /**
     * @brief Key 타입 분류
     * @note 키보드, 마우스 등 입력 장치를 관리하는 Enum
     */
    enum class EKeyType : uint8
    {
        Keyboard,
        Mouse,
        MouseAxis,
        Gamepad,
        GamepadAxis,
        Touch,
        END
    };
} // namespace TDME