#pragma once

#include "Core/CoreMacros.h"
#include "Core/CoreTypes.h"
#include "Core/Types/Color.h"

namespace TDME
{
    /**
     * @brief 32비트 색상 값을 저장하는 구조체 (ARGB)
     * @note GPU에 전달하기 위한 색상 포멧
     */
    struct Color32
    {
        uint32 Value;

        constexpr Color32() : Value(0xFFFFFFFF) {}
        constexpr Color32(uint32 argb) : Value(argb) {}
        constexpr Color32(uint8 r, uint8 g, uint8 b, uint8 a = 255)
            : Value((a << 24) | (r << 16) | (g << 8) | b) {}

        /**
         * @brief Color 객체를 Color32 객체로 변환
         * @param color Color 객체
         * @return Color32 객체
         */
        static FORCE_INLINE Color32 FromColor(const Color& color)
        {
            return Color32(
                static_cast<uint8>(color.R * 255),
                static_cast<uint8>(color.G * 255),
                static_cast<uint8>(color.B * 255),
                static_cast<uint8>(color.A * 255));
        }

        FORCE_INLINE constexpr uint8 A() const { return (Value >> 24) & 0xFF; }
        FORCE_INLINE constexpr uint8 R() const { return (Value >> 16) & 0xFF; }
        FORCE_INLINE constexpr uint8 G() const { return (Value >> 8) & 0xFF; }
        FORCE_INLINE constexpr uint8 B() const { return Value & 0xFF; }
    };
} // namespace TDME