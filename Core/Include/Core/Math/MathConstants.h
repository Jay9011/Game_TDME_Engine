#pragma once

namespace TDME
{
    /**
    * @brief 수학 상수
    */
    namespace Math {
        constexpr float Pi = 3.14159265358979323846f;
        constexpr float Pi2 = Pi * 2.0f;
        constexpr float PiHalf = Pi / 2.0f;
        constexpr float PiQuarter = Pi / 4.0f;

        constexpr float DegToRad = Pi / 180.0f; // 1도를 라디안으로 변환
        constexpr float RadToDeg = 180.0f / Pi; // 1라디안을 도로 변환

        constexpr float Epsilon = 1.1920928955078125e-07f;
    }
}