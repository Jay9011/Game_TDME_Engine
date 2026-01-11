#include "pch.h"
#include "Platform_Windows/Input/Win32KeyMapping.h"

#include <Engine/Input/EKeys.h>
#include <unordered_map>

namespace TDME
{
    /**
     * @brief VK ↔ Key 매핑 테이블
     */
    static const std::unordered_map<UINT, const Key*>& GetVKToKeyMap()
    {
        static std::unordered_map<UINT, const Key*> s_vkToKey = {
            //////////////////////////////////////////////////////////////
            // 알파벳
            //////////////////////////////////////////////////////////////
            {'A', &EKeys::A},
            {'B', &EKeys::B},
            {'C', &EKeys::C},
            {'D', &EKeys::D},
            {'E', &EKeys::E},
            {'F', &EKeys::F},
            {'G', &EKeys::G},
            {'H', &EKeys::H},
            {'I', &EKeys::I},
            {'J', &EKeys::J},
            {'K', &EKeys::K},
            {'L', &EKeys::L},
            {'M', &EKeys::M},
            {'N', &EKeys::N},
            {'O', &EKeys::O},
            {'P', &EKeys::P},
            {'Q', &EKeys::Q},
            {'R', &EKeys::R},
            {'S', &EKeys::S},
            {'T', &EKeys::T},
            {'U', &EKeys::U},
            {'V', &EKeys::V},
            {'W', &EKeys::W},
            {'X', &EKeys::X},
            {'Y', &EKeys::Y},
            {'Z', &EKeys::Z},

            //////////////////////////////////////////////////////////////
            // 숫자
            //////////////////////////////////////////////////////////////
            {'0', &EKeys::Zero},
            {'1', &EKeys::One},
            {'2', &EKeys::Two},
            {'3', &EKeys::Three},
            {'4', &EKeys::Four},
            {'5', &EKeys::Five},
            {'6', &EKeys::Six},
            {'7', &EKeys::Seven},
            {'8', &EKeys::Eight},
            {'9', &EKeys::Nine},

            //////////////////////////////////////////////////////////////
            // 기능키
            //////////////////////////////////////////////////////////////
            {VK_F1, &EKeys::F1},
            {VK_F2, &EKeys::F2},
            {VK_F3, &EKeys::F3},
            {VK_F4, &EKeys::F4},
            {VK_F5, &EKeys::F5},
            {VK_F6, &EKeys::F6},
            {VK_F7, &EKeys::F7},
            {VK_F8, &EKeys::F8},
            {VK_F9, &EKeys::F9},
            {VK_F10, &EKeys::F10},
            {VK_F11, &EKeys::F11},
            {VK_F12, &EKeys::F12},

            //////////////////////////////////////////////////////////////
            // Numpad
            //////////////////////////////////////////////////////////////
            {VK_NUMPAD0, &EKeys::NumpadZero},
            {VK_NUMPAD1, &EKeys::NumpadOne},
            {VK_NUMPAD2, &EKeys::NumpadTwo},
            {VK_NUMPAD3, &EKeys::NumpadThree},
            {VK_NUMPAD4, &EKeys::NumpadFour},
            {VK_NUMPAD5, &EKeys::NumpadFive},
            {VK_NUMPAD6, &EKeys::NumpadSix},
            {VK_NUMPAD7, &EKeys::NumpadSeven},
            {VK_NUMPAD8, &EKeys::NumpadEight},
            {VK_NUMPAD9, &EKeys::NumpadNine},

            //////////////////////////////////////////////////////////////
            // 방향키
            //////////////////////////////////////////////////////////////
            {VK_LEFT, &EKeys::Left},
            {VK_UP, &EKeys::Up},
            {VK_RIGHT, &EKeys::Right},
            {VK_DOWN, &EKeys::Down},

            //////////////////////////////////////////////////////////////
            // 특수키
            //////////////////////////////////////////////////////////////
            {VK_BACK, &EKeys::Backspace},
            {VK_TAB, &EKeys::Tab},
            {VK_RETURN, &EKeys::Enter},
            {VK_CAPITAL, &EKeys::CapsLock},
            {VK_ESCAPE, &EKeys::Escape},
            {VK_SPACE, &EKeys::SpaceBar},

            //////////////////////////////////////////////////////////////
            // Shift, Control, Alt
            //////////////////////////////////////////////////////////////
            {VK_SHIFT, &EKeys::LeftShift},
            {VK_CONTROL, &EKeys::LeftControl},
            {VK_MENU, &EKeys::LeftAlt},
            {VK_LSHIFT, &EKeys::LeftShift},
            {VK_RSHIFT, &EKeys::RightShift},
            {VK_LCONTROL, &EKeys::LeftControl},
            {VK_RCONTROL, &EKeys::RightControl},
            {VK_LMENU, &EKeys::LeftAlt},
            {VK_RMENU, &EKeys::RightAlt},

            //////////////////////////////////////////////////////////////
            // 잘 안쓰는 특수키
            //////////////////////////////////////////////////////////////
            {VK_PRIOR, &EKeys::PageUp},
            {VK_NEXT, &EKeys::PageDown},
            {VK_END, &EKeys::End},
            {VK_HOME, &EKeys::Home},
            {VK_INSERT, &EKeys::Insert},
            {VK_DELETE, &EKeys::Delete},
            {VK_PRINT, &EKeys::PrintScreen},
            {VK_SCROLL, &EKeys::ScrollLock},
            {VK_NUMLOCK, &EKeys::NumLock},

            //////////////////////////////////////////////////////////////
            // 기타 키
            //////////////////////////////////////////////////////////////
            {VK_MULTIPLY, &EKeys::Multiply},
            {VK_ADD, &EKeys::Add},
            {VK_SUBTRACT, &EKeys::Subtract},
            {VK_DECIMAL, &EKeys::Dot},
            {VK_DIVIDE, &EKeys::Divide},

            //////////////////////////////////////////////////////////////
            // 마우스 버튼
            //////////////////////////////////////////////////////////////
            {VK_LBUTTON, &EKeys::LeftMouseButton},
            {VK_RBUTTON, &EKeys::RightMouseButton},
            {VK_MBUTTON, &EKeys::MiddleMouseButton},
            {VK_XBUTTON1, &EKeys::ThumbMouseButton},
            {VK_XBUTTON2, &EKeys::ThumbMouseButton2},
        };
        return s_vkToKey;
    } // GetVKToKeyMap()

    const Key& VKToKey(UINT virtualKey)
    {
        const auto& map = GetVKToKeyMap();

        auto it = map.find(virtualKey);
        if (it != map.end())
        {
            return *it->second;
        }
        return EKeys::Invalid;
    }

    // NOTE: 현재는 O(N). 자주 사용 될 경우 O(1)로 변경 필요 (역방향 매핑 테이블 추가)
    UINT KeyToVK(const Key& key)
    {
        const auto& map = GetVKToKeyMap();

        for (const auto& [vk, k] : map)
        {
            if (*k == key)
            {
                return vk;
            }
        }
        return 0;
    }

} // namespace TDME