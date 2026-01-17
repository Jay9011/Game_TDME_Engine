#include "pch.h"
#include "Platform_Windows/Window/Win32Window.h"

namespace TDME
{
    static constexpr const WCHAR* WINDOW_CLASS_NAME = L"TDME_WindowClass";

    Win32Window::Win32Window() : m_hWnd(nullptr), m_width(0), m_height(0), m_isOpen(false)
    {
    }

    Win32Window::~Win32Window()
    {
        if (m_hWnd)
        {
            DestroyWindow(m_hWnd);
            m_hWnd = nullptr;
        }
    }

    bool Win32Window::Create(int32 width, int32 height, const char* title)
    {
        HINSTANCE hInstance = GetModuleHandle(nullptr);

        // Title 변환
        wstring wideTitle = ToWideString(title);

        // 창 크기 조정
        RECT  rect  = {0, 0, width, height};
        DWORD style = WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_OVERLAPPEDWINDOW;
        AdjustWindowRect(&rect, style, FALSE);

        // 화면 크기 조정
        int32 windowWidth  = rect.right - rect.left;
        int32 windowHeight = rect.bottom - rect.top;
        int32 screenWidth  = GetSystemMetrics(SM_CXSCREEN);
        int32 screenHeight = GetSystemMetrics(SM_CYSCREEN);
        int32 posX         = (screenWidth - windowWidth) / 2;
        int32 posY         = (screenHeight - windowHeight) / 2;

        // 창 생성
        m_hWnd = CreateWindowExW(
            WS_EX_APPWINDOW,
            WINDOW_CLASS_NAME,
            wideTitle.c_str(),
            style,
            posX, posY,                // CW_USEDEFAULT : 이전 윈도우 위치 사용
            windowWidth, windowHeight, // CW_USEDEFAULT : 이전 윈도우 크기 사용
            nullptr,
            nullptr,
            hInstance,
            this);

        if (!m_hWnd)
        {
            return false;
        }

        m_width  = width;
        m_height = height;
        m_isOpen = true;

        ShowWindow(m_hWnd, SW_SHOW);
        SetForegroundWindow(m_hWnd);
        SetFocus(m_hWnd);
        UpdateWindow(m_hWnd);

        return true;
    } // Create

    void Win32Window::SetTitle(const char* title)
    {
        wstring wideTitle = ToWideString(title);
        SetWindowTextW(m_hWnd, wideTitle.c_str());
    }

    bool Win32Window::ProcessMessage(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam, LRESULT& outResult)
    {
        switch (message)
        {
        case WM_SIZE:
            OnResize(LOWORD(lParam), HIWORD(lParam));
            outResult = 0;
            break;
        case WM_CLOSE:
            OnClose();
            outResult = 0;
            return true;
        case WM_DESTROY:
            PostQuitMessage(0);
            outResult = 0;
            return true;
        }

        return false;
    }

    //////////////////////////////////////////////////////////////
    // Getter / Setter
    //////////////////////////////////////////////////////////////

    bool Win32Window::IsOpen() const
    {
        return m_isOpen;
    }

    int32 Win32Window::GetWidth() const
    {
        return m_width;
    }

    int32 Win32Window::GetHeight() const
    {
        return m_height;
    }

    void* Win32Window::GetNativeHandle() const
    {
        return m_hWnd;
    }

    //////////////////////////////////////////////////////////////
    // Private Functions
    //////////////////////////////////////////////////////////////

    void Win32Window::OnResize(int32 width, int32 height)
    {
        m_width  = width;
        m_height = height;
    }

    void Win32Window::OnClose()
    {
        m_isOpen = false;
    }

    wstring Win32Window::ToWideString(const string& str)
    {
        if (str.empty())
        {
            return wstring();
        }

        int32 len = MultiByteToWideChar(CP_UTF8, 0, str.c_str(), static_cast<int32>(str.size()), nullptr, 0);

        wstring wideStr(len, 0);
        MultiByteToWideChar(CP_UTF8, 0, str.c_str(), static_cast<int32>(str.size()), wideStr.data(), len);

        return wideStr;
    } // ToWideString
} // namespace TDME
