#pragma once

#include "Key.h"

namespace TDME
{
    /**
     * @brief 미리 정의된 키 상수
     * @details Unreal Engine 기반 EKey 와 유사한 구조
     * @see https://github.com/EpicGames/UnrealEngine/blob/release/Engine/Source/Runtime/InputCore/Classes/InputCoreTypes.h
     * @note 기반은 Unreal Engine 이지만, 우선은 쓸만한 키부터 정의 함
     */
    struct EKeys
    {
        //////////////////////////////////////////////////////////////
        // 마우스
        //////////////////////////////////////////////////////////////

        static const Key MouseX;
        static const Key MouseY;
        static const Key Mouse2D;
        static const Key MouseScrollUp;
        static const Key MouseScrollDown;
        static const Key MouseWheelAxis;

        static const Key LeftMouseButton;
        static const Key RightMouseButton;
        static const Key MiddleMouseButton;
        static const Key ThumbMouseButton;
        static const Key ThumbMouseButton2;

        //////////////////////////////////////////////////////////////
        // 특수키
        //////////////////////////////////////////////////////////////

        static const Key Backspace;
        static const Key Enter;
        static const Key Escape;
        static const Key Tab;
        static const Key CapsLock;
        static const Key SpaceBar;

        static const Key Insert;
        static const Key Delete;
        static const Key Home;
        static const Key End;
        static const Key PageUp;
        static const Key PageDown;

        static const Key PrintScreen;
        static const Key ScrollLock;
        static const Key Pause;
        static const Key NumLock;

        //////////////////////////////////////////////////////////////
        // 방향키
        //////////////////////////////////////////////////////////////

        static const Key Left;
        static const Key Up;
        static const Key Right;
        static const Key Down;

        //////////////////////////////////////////////////////////////
        // 알파벳
        //////////////////////////////////////////////////////////////

        static const Key A;
        static const Key B;
        static const Key C;
        static const Key D;
        static const Key E;
        static const Key F;
        static const Key G;
        static const Key H;
        static const Key I;
        static const Key J;
        static const Key K;
        static const Key L;
        static const Key M;
        static const Key N;
        static const Key O;
        static const Key P;
        static const Key Q;
        static const Key R;
        static const Key S;
        static const Key T;
        static const Key U;
        static const Key V;
        static const Key W;
        static const Key X;
        static const Key Y;
        static const Key Z;

        //////////////////////////////////////////////////////////////
        // 숫자 키 (위쪽 Number)
        //////////////////////////////////////////////////////////////

        static const Key Zero;
        static const Key One;
        static const Key Two;
        static const Key Three;
        static const Key Four;
        static const Key Five;
        static const Key Six;
        static const Key Seven;
        static const Key Eight;
        static const Key Nine;

        //////////////////////////////////////////////////////////////
        // 숫자 키 (Numpad)
        //////////////////////////////////////////////////////////////

        static const Key NumpadZero;
        static const Key NumpadOne;
        static const Key NumpadTwo;
        static const Key NumpadThree;
        static const Key NumpadFour;
        static const Key NumpadFive;
        static const Key NumpadSix;
        static const Key NumpadSeven;
        static const Key NumpadEight;
        static const Key NumpadNine;

        static const Key Multiply;
        static const Key Add;
        static const Key Subtract;
        static const Key Dot;
        static const Key Divide;

        //////////////////////////////////////////////////////////////
        // 기능 키
        //////////////////////////////////////////////////////////////

        static const Key F1;
        static const Key F2;
        static const Key F3;
        static const Key F4;
        static const Key F5;
        static const Key F6;
        static const Key F7;
        static const Key F8;
        static const Key F9;
        static const Key F10;
        static const Key F11;
        static const Key F12;

        //////////////////////////////////////////////////////////////
        // Alt, Shift, Control
        //////////////////////////////////////////////////////////////

        static const Key LeftAlt;
        static const Key RightAlt;
        static const Key LeftShift;
        static const Key RightShift;
        static const Key LeftControl;
        static const Key RightControl;

        //////////////////////////////////////////////////////////////
        // 기타 키 (우선은 Shift 없이)
        //////////////////////////////////////////////////////////////

        static const Key Tilde;        // ~
        static const Key Hyphen;       // -
        static const Key Equals;       // =
        static const Key LeftBracket;  // [
        static const Key RightBracket; // ]
        static const Key Backslash;    // (\)
        static const Key Semicolon;    // ;
        static const Key Apostrophe;   // '
        static const Key Comma;        // ,
        static const Key Period;       // .
        static const Key Slash;        // /

        //////////////////////////////////////////////////////////////
        // 유효하지 않은 키
        //////////////////////////////////////////////////////////////

        static const Key Invalid;
    };
} // namespace TDME