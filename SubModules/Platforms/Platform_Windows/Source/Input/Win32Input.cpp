#include "pch.h"
#include "Platform_Windows/Input/Win32Input.h"

namespace TDME
{
    Win32Input::Win32Input()
        : m_hWnd(nullptr), m_currentKeys{}, m_previousKeys{}, m_currentMouseButtons{}, m_previousMouseButtons{},
          m_mousePosition(0, 0)
    {
    }

    bool Win32Input::Initialize(IWindow* window)
    {
        m_hWnd = static_cast<HWND>(window->GetNativeHandle());
        return m_hWnd != nullptr;
    }

    void Win32Input::Update()
    {
        // 이전 상태 저장
        m_previousKeys         = m_currentKeys;
        m_previousMouseButtons = m_currentMouseButtons;

        // 키보드 상태 갱신
        for (size_t i = 0; i < KEY_COUNT; ++i)
        {
            m_currentKeys[i] = (GetAsyncKeyState(static_cast<int>(i)) & 0x8000) != 0; // GetAsyncKeyState 함수는 키가 눌려있는지 여부를 반환하는데, 최상위 비트가 1인 경우 눌려있음을 의미
        }

        // 마우스 상태 갱신
        for (size_t i = 0; i < MOUSE_BUTTON_COUNT; ++i)
        {
            m_currentMouseButtons[i] = (GetAsyncKeyState(static_cast<int>(i)) & 0x8000) != 0;
        }

        POINT point;
        if (GetCursorPos(&point) && ScreenToClient(m_hWnd, &point))
        {
            m_mousePosition = Vector2(static_cast<float>(point.x), static_cast<float>(point.y));
        }
    }

    bool Win32Input::IsKeyDown(EKeyCode key) const
    {
        return m_currentKeys[static_cast<size_t>(key)];
    }
    bool Win32Input::IsKeyPressed(EKeyCode key) const
    {
        size_t idx = static_cast<size_t>(key);
        return m_currentKeys[idx] && !m_previousKeys[idx];
    }
    bool Win32Input::IsKeyReleased(EKeyCode key) const
    {
        size_t idx = static_cast<size_t>(key);
        return !m_currentKeys[idx] && m_previousKeys[idx];
    }

    Vector2 Win32Input::GetMousePosition() const
    {
        return m_mousePosition;
    }

    bool Win32Input::IsMouseButtonDown(EMouseButton button) const
    {
        return m_currentMouseButtons[static_cast<size_t>(button)];
    }
    bool Win32Input::IsMouseButtonPressed(EMouseButton button) const
    {
        size_t idx = static_cast<size_t>(button);
        return m_currentMouseButtons[idx] && !m_previousMouseButtons[idx];
    }
    bool Win32Input::IsMouseButtonReleased(EMouseButton button) const
    {
        size_t idx = static_cast<size_t>(button);
        return !m_currentMouseButtons[idx] && m_previousMouseButtons[idx];
    }

} // namespace TDME