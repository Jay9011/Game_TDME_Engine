#pragma once

#include "Core/CoreTypes.h"

namespace TDME
{
    // NOTE: 추후 다시 확인
    /**
     * @brief 키보드 키 코드
     * @note Window Virtual Key Codes 기반
     * @see <winuser.h>
     * @see https://learn.microsoft.com/en-us/windows/win32/inputdev/virtual-key-codes
     */
    enum class EKeyCode : uint8
    {
        // clang-format off

        // 알파벳
        A = 0x41, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z,

        // 숫자
        Num0 = 0x30, Num1, Num2, Num3, Num4, Num5, Num6, Num7, Num8, Num9,

        // 기능키
        F1 = 0x70, F2, F3, F4, F5, F6, F7, F8, F9, F10, F11, F12,

        // Numpad
        Numpad0 = 0x60, Numpad1, Numpad2, Numpad3, Numpad4, Numpad5, Numpad6, Numpad7, Numpad8, Numpad9,

        // clang-format on

        // 방향키
        Left  = 0x25,
        Up    = 0x26,
        Right = 0x27,
        Down  = 0x28,

        // 특수키
        Backspace = 0x08,
        Tab       = 0x09,
        Enter     = 0x0D,
        Shift     = 0x10,
        Control   = 0x11,
        Alt       = 0x12,
        CapsLock  = 0x14,
        Escape    = 0x1B,
        Space     = 0x20,

        // 잘 안쓰는 특수키
        Pause       = 0x13,
        PageUp      = 0x21,
        PageDown    = 0x22,
        End         = 0x23,
        Home        = 0x24,
        Insert      = 0x2D,
        Delete      = 0x2E,
        PrintScreen = 0x2C,
        ScrollLock  = 0x91,
        NumLock     = 0x90,

        // 기타 키
        Multiply = 0x6A,
        Add      = 0x6B,
        Subtract = 0x6D,
        Dot      = 0x6E, // VK_DECIMAL
        Divide   = 0x6F,

        // 키 개수 카운터
        COUNT = 0xFF
    };
} // namespace TDME