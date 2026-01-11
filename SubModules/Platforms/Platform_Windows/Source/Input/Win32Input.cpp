#include "pch.h"
#include "Platform_Windows/Input/Win32Input.h"

#include <Engine/ApplicationCore/IWindow.h>

namespace TDME
{
    bool Win32Input::Initialize(IWindow* window)
    {
        if (!window)
        {
            return false;
        }

        m_hWnd = static_cast<HWND>(window->GetNativeHandle());
        return m_hWnd != nullptr;
    }

    void Win32Input::Update()
    {
        // 이전 상태 저장
        m_previousKeys = m_currentKeys;
    }

    bool Win32Input::IsKeyDown(const Key& key) const
    {
        return m_currentKeys.count(key) > 0;
    }
    bool Win32Input::IsKeyPressed(const Key& key) const
    {
        return m_currentKeys.count(key) > 0 && m_previousKeys.count(key) == 0;
    }
    bool Win32Input::IsKeyReleased(const Key& key) const
    {
        return m_currentKeys.count(key) == 0 && m_previousKeys.count(key) > 0;
    }

    Vector2 Win32Input::GetMousePosition() const
    {
        return m_mousePosition;
    }

    void Win32Input::OnKeyDown(const Key& key)
    {
        m_currentKeys.insert(key);
    }

    void Win32Input::OnKeyUp(const Key& key)
    {
        m_currentKeys.erase(key);
    }

    void Win32Input::OnMouseMove(int32 x, int32 y)
    {
        m_mousePosition.X = static_cast<float>(x);
        m_mousePosition.Y = static_cast<float>(y);
    }

} // namespace TDME