#include "pch.h"

#include <Engine/Input/EKeys.h>

namespace TDME
{
    //////////////////////////////////////////////////////////////
    // 마우스
    //////////////////////////////////////////////////////////////

    const Key EKeys::MouseX          = DEFINE_MOUSE_AXIS(MouseX);
    const Key EKeys::MouseY          = DEFINE_MOUSE_AXIS(MouseY);
    const Key EKeys::Mouse2D         = DEFINE_MOUSE_AXIS(Mouse2D);
    const Key EKeys::MouseScrollUp   = DEFINE_MOUSE_KEY(MouseScrollUp);
    const Key EKeys::MouseScrollDown = DEFINE_MOUSE_KEY(MouseScrollDown);
    const Key EKeys::MouseWheelAxis  = DEFINE_MOUSE_AXIS(MouseWheelAxis);

    const Key EKeys::LeftMouseButton   = DEFINE_MOUSE_KEY(LeftMouseButton);
    const Key EKeys::RightMouseButton  = DEFINE_MOUSE_KEY(RightMouseButton);
    const Key EKeys::MiddleMouseButton = DEFINE_MOUSE_KEY(MiddleMouseButton);
    const Key EKeys::ThumbMouseButton  = DEFINE_MOUSE_KEY(ThumbMouseButton);
    const Key EKeys::ThumbMouseButton2 = DEFINE_MOUSE_KEY(ThumbMouseButton2);

    //////////////////////////////////////////////////////////////
    // 특수키
    //////////////////////////////////////////////////////////////

    const Key EKeys::Backspace = DEFINE_KEY(Backspace);
    const Key EKeys::Enter     = DEFINE_KEY(Enter);
    const Key EKeys::Escape    = DEFINE_KEY(Escape);
    const Key EKeys::Tab       = DEFINE_KEY(Tab);
    const Key EKeys::CapsLock  = DEFINE_KEY(CapsLock);
    const Key EKeys::SpaceBar  = DEFINE_KEY(SpaceBar);

    const Key EKeys::Insert   = DEFINE_KEY(Insert);
    const Key EKeys::Delete   = DEFINE_KEY(Delete);
    const Key EKeys::Home     = DEFINE_KEY(Home);
    const Key EKeys::End      = DEFINE_KEY(End);
    const Key EKeys::PageUp   = DEFINE_KEY(PageUp);
    const Key EKeys::PageDown = DEFINE_KEY(PageDown);

    const Key EKeys::PrintScreen = DEFINE_KEY(PrintScreen);
    const Key EKeys::ScrollLock  = DEFINE_KEY(ScrollLock);
    const Key EKeys::Pause       = DEFINE_KEY(Pause);
    const Key EKeys::NumLock     = DEFINE_KEY(NumLock);

    //////////////////////////////////////////////////////////////
    // 방향키
    //////////////////////////////////////////////////////////////

    const Key EKeys::Left  = DEFINE_KEY(Left);
    const Key EKeys::Up    = DEFINE_KEY(Up);
    const Key EKeys::Right = DEFINE_KEY(Right);
    const Key EKeys::Down  = DEFINE_KEY(Down);

    //////////////////////////////////////////////////////////////
    // 알파벳
    //////////////////////////////////////////////////////////////

    const Key EKeys::A = DEFINE_KEY(A);
    const Key EKeys::B = DEFINE_KEY(B);
    const Key EKeys::C = DEFINE_KEY(C);
    const Key EKeys::D = DEFINE_KEY(D);
    const Key EKeys::E = DEFINE_KEY(E);
    const Key EKeys::F = DEFINE_KEY(F);
    const Key EKeys::G = DEFINE_KEY(G);
    const Key EKeys::H = DEFINE_KEY(H);
    const Key EKeys::I = DEFINE_KEY(I);
    const Key EKeys::J = DEFINE_KEY(J);
    const Key EKeys::K = DEFINE_KEY(K);
    const Key EKeys::L = DEFINE_KEY(L);
    const Key EKeys::M = DEFINE_KEY(M);
    const Key EKeys::N = DEFINE_KEY(N);
    const Key EKeys::O = DEFINE_KEY(O);
    const Key EKeys::P = DEFINE_KEY(P);
    const Key EKeys::Q = DEFINE_KEY(Q);
    const Key EKeys::R = DEFINE_KEY(R);
    const Key EKeys::S = DEFINE_KEY(S);
    const Key EKeys::T = DEFINE_KEY(T);
    const Key EKeys::U = DEFINE_KEY(U);
    const Key EKeys::V = DEFINE_KEY(V);
    const Key EKeys::W = DEFINE_KEY(W);
    const Key EKeys::X = DEFINE_KEY(X);
    const Key EKeys::Y = DEFINE_KEY(Y);
    const Key EKeys::Z = DEFINE_KEY(Z);

    //////////////////////////////////////////////////////////////
    // 숫자 키
    //////////////////////////////////////////////////////////////

    const Key EKeys::Zero  = DEFINE_KEY(Zero);
    const Key EKeys::One   = DEFINE_KEY(One);
    const Key EKeys::Two   = DEFINE_KEY(Two);
    const Key EKeys::Three = DEFINE_KEY(Three);
    const Key EKeys::Four  = DEFINE_KEY(Four);
    const Key EKeys::Five  = DEFINE_KEY(Five);
    const Key EKeys::Six   = DEFINE_KEY(Six);
    const Key EKeys::Seven = DEFINE_KEY(Seven);
    const Key EKeys::Eight = DEFINE_KEY(Eight);
    const Key EKeys::Nine  = DEFINE_KEY(Nine);

    //////////////////////////////////////////////////////////////
    // 숫자 키 (Numpad)
    //////////////////////////////////////////////////////////////

    const Key EKeys::NumpadZero  = DEFINE_KEY(NumpadZero);
    const Key EKeys::NumpadOne   = DEFINE_KEY(NumpadOne);
    const Key EKeys::NumpadTwo   = DEFINE_KEY(NumpadTwo);
    const Key EKeys::NumpadThree = DEFINE_KEY(NumpadThree);
    const Key EKeys::NumpadFour  = DEFINE_KEY(NumpadFour);
    const Key EKeys::NumpadFive  = DEFINE_KEY(NumpadFive);
    const Key EKeys::NumpadSix   = DEFINE_KEY(NumpadSix);
    const Key EKeys::NumpadSeven = DEFINE_KEY(NumpadSeven);
    const Key EKeys::NumpadEight = DEFINE_KEY(NumpadEight);
    const Key EKeys::NumpadNine  = DEFINE_KEY(NumpadNine);

    const Key EKeys::Multiply = DEFINE_KEY(Multiply);
    const Key EKeys::Add      = DEFINE_KEY(Add);
    const Key EKeys::Subtract = DEFINE_KEY(Subtract);
    const Key EKeys::Dot      = DEFINE_KEY(Dot);
    const Key EKeys::Divide   = DEFINE_KEY(Divide);

    //////////////////////////////////////////////////////////////
    // 기능 키
    //////////////////////////////////////////////////////////////

    const Key EKeys::F1  = DEFINE_KEY(F1);
    const Key EKeys::F2  = DEFINE_KEY(F2);
    const Key EKeys::F3  = DEFINE_KEY(F3);
    const Key EKeys::F4  = DEFINE_KEY(F4);
    const Key EKeys::F5  = DEFINE_KEY(F5);
    const Key EKeys::F6  = DEFINE_KEY(F6);
    const Key EKeys::F7  = DEFINE_KEY(F7);
    const Key EKeys::F8  = DEFINE_KEY(F8);
    const Key EKeys::F9  = DEFINE_KEY(F9);
    const Key EKeys::F10 = DEFINE_KEY(F10);
    const Key EKeys::F11 = DEFINE_KEY(F11);
    const Key EKeys::F12 = DEFINE_KEY(F12);

    //////////////////////////////////////////////////////////////
    // Alt, Shift, Control
    //////////////////////////////////////////////////////////////

    const Key EKeys::LeftAlt      = DEFINE_KEY(LeftAlt);
    const Key EKeys::RightAlt     = DEFINE_KEY(RightAlt);
    const Key EKeys::LeftShift    = DEFINE_KEY(LeftShift);
    const Key EKeys::RightShift   = DEFINE_KEY(RightShift);
    const Key EKeys::LeftControl  = DEFINE_KEY(LeftControl);
    const Key EKeys::RightControl = DEFINE_KEY(RightControl);

    //////////////////////////////////////////////////////////////
    // 기타 키
    //////////////////////////////////////////////////////////////

    const Key EKeys::Tilde        = DEFINE_KEY(Tilde);
    const Key EKeys::Hyphen       = DEFINE_KEY(Hyphen);
    const Key EKeys::Equals       = DEFINE_KEY(Equals);
    const Key EKeys::LeftBracket  = DEFINE_KEY(LeftBracket);
    const Key EKeys::RightBracket = DEFINE_KEY(RightBracket);
    const Key EKeys::Backslash    = DEFINE_KEY(Backslash);
    const Key EKeys::Semicolon    = DEFINE_KEY(Semicolon);
    const Key EKeys::Apostrophe   = DEFINE_KEY(Apostrophe);
    const Key EKeys::Comma        = DEFINE_KEY(Comma);
    const Key EKeys::Period       = DEFINE_KEY(Period);
    const Key EKeys::Slash        = DEFINE_KEY(Slash);

    //////////////////////////////////////////////////////////////
    // 유효하지 않은 키
    //////////////////////////////////////////////////////////////

    const Key EKeys::Invalid = Key();
} // namespace TDME