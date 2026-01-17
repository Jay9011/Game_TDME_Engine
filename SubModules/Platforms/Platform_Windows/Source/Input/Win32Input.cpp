#include "pch.h"
#include "Platform_Windows/Input/Win32Input.h"

#include <Core/Math/TVector2.h>
#include <Engine/ApplicationCore/IWindow.h>
#include <Engine/Input/EKeys.h>

#include "Platform_Windows/Input/Win32KeyMapping.h"
#include <Windows.h>
#include <windowsx.h>

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

    Vector2 Win32Input::GetAxis2D(const Key& axis) const
    {
        if (axis == EKeys::Mouse2D)
        {
            return m_mousePosition;
        }
        return Vector2::Zero();
    }

    float Win32Input::GetAxisValue(const Key& axis) const
    {
        return 0.0f;
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

    bool Win32Input::ProcessMessage(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam, LRESULT& outResult)
    {
        switch (message)
        {
        case WM_KEYDOWN:
        case WM_SYSKEYDOWN:
            OnKeyDown(VKToKey(static_cast<UINT>(wParam)));
            break;
        case WM_KEYUP:
        case WM_SYSKEYUP:
            OnKeyUp(VKToKey(static_cast<UINT>(wParam)));
            break;
        case WM_MOUSEMOVE:
            OnMouseMove(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
            break;
        case WM_LBUTTONDOWN:
            OnKeyDown(EKeys::LeftMouseButton);
            break;
        case WM_LBUTTONUP:
            OnKeyUp(EKeys::LeftMouseButton);
            break;
        case WM_RBUTTONDOWN:
            OnKeyDown(EKeys::RightMouseButton);
            break;
        case WM_RBUTTONUP:
            OnKeyUp(EKeys::RightMouseButton);
            break;
        case WM_MBUTTONDOWN:
            OnKeyDown(EKeys::MiddleMouseButton);
            break;
        case WM_MBUTTONUP:
            OnKeyUp(EKeys::MiddleMouseButton);
            break;
        }

        return false;
    }

} // namespace TDME