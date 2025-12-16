#pragma once

#include "Core/CoreMacros.h"
#include "Core/CoreTypes.h"

namespace TDME
{
    struct Color
    {
        float R, G, B, A;

        constexpr Color() : R(0), G(0), B(0), A(1) {}
        constexpr Color(float r, float g, float b, float a = 1) : R(r), G(g), B(b), A(a) {}

        /**
        * @brief 16진수 색상 값을 파싱하여 Color 객체로 변환
        * @param rgb 16진수 색상 값 (0xRRGGBB)
        * @return Color 객체
        */
        static FORCE_INLINE Color FromHexRGB(uint32 rgb)
        {
            constexpr float inv255 = 1.0f / 255.0f; // 255로 나누어 0-1 범위로 변환
            return Color(
                ((rgb >> 16) & 0xFF) * inv255,
                ((rgb >> 8) & 0xFF) * inv255,
                ((rgb >> 0) & 0xFF) * inv255
            );
        }

        /**
        * @brief 16진수 색상 값을 파싱하여 Color 객체로 변환
        * @param rgba 16진수 색상 값 (0xRRGGBBAA)
        * @return Color 객체
        */
        static FORCE_INLINE Color FromHexRGBA(uint32 rgba)
        {
            constexpr float inv255 = 1.0f / 255.0f; // 255로 나누어 0-1 범위로 변환
            return Color(
                ((rgba >> 24) & 0xFF) * inv255,
                ((rgba >> 16) & 0xFF) * inv255,
                ((rgba >> 8) & 0xFF) * inv255,
                ((rgba >> 0) & 0xFF) * inv255
            );
        }

        /**
        * @brief 16진수 색상 값을 파싱하여 Color 객체로 변환
        * @param argb 16진수 색상 값 (0xAARRGGBB)
        * @return Color 객체
        */
        static FORCE_INLINE Color FromHexARGB(uint32 argb)
        {
            constexpr float inv255 = 1.0f / 255.0f; // 255로 나누어 0-1 범위로 변환
            return Color(
                ((argb >> 16) & 0xFF) * inv255,
                ((argb >> 8) & 0xFF) * inv255,
                ((argb >> 0) & 0xFF) * inv255,
                ((argb >> 24) & 0xFF) * inv255
            );
        }

        /**
        * @brief 8비트 색상 값을 파싱하여 Color 객체로 변환
        * @param r 빨간색 값 (0-255)
        * @param g 초록색 값 (0-255)
        * @param b 파란색 값 (0-255)
        * @param a 알파 값 (0-255)
        * @return Color 객체
        */
        static FORCE_INLINE Color FromBytes(uint8 r, uint8 g, uint8 b, uint8 a = 255)
        {
            constexpr float inv255 = 1.0f / 255.0f; // 255로 나누어 0-1 범위로 변환
            return Color(r * inv255, g * inv255, b * inv255, a * inv255);
        }

        // =============================== 미리 정의된 색상 =============================== //

        static constexpr Color Black()  { return Color(0, 0, 0, 1); }
        static constexpr Color White()  { return Color(1, 1, 1, 1); }
        static constexpr Color Red()    { return Color(1, 0, 0, 1); }
        static constexpr Color Green()  { return Color(0, 1, 0, 1); }
        static constexpr Color Blue()   { return Color(0, 0, 1, 1); }
        static constexpr Color Yellow() { return Color(1, 1, 0, 1); }
        static constexpr Color Magenta(){ return Color(1, 0, 1, 1); }
        static constexpr Color Cyan()   { return Color(0, 1, 1, 1); }
    };

    namespace Colors {
        INLINE constexpr Color BLACK    = Color::Black();
        INLINE constexpr Color WHITE    = Color::White();
        INLINE constexpr Color RED      = Color::Red();
        INLINE constexpr Color GREEN    = Color::Green();
        INLINE constexpr Color BLUE     = Color::Blue();
        INLINE constexpr Color YELLOW   = Color::Yellow();
        INLINE constexpr Color MAGENTA  = Color::Magenta();
        INLINE constexpr Color CYAN     = Color::Cyan();
    }
}