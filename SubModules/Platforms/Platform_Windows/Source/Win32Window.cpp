#include "pch.h"
#include <string>
#include <stringapiset.h>
#include <winnls.h>
#include <winuser.h>
#include "Platform_Windows/Win32Window.h"

namespace TDME
{
    bool Win32Window::s_classRegistered = false;

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
        m_isOpen = false;
    }

    bool Win32Window::Create(int32 width, int32 height, const char* title)
    {
        HINSTANCE hInstance = GetModuleHandle(nullptr);

        // Window 클래스 등록
        if (!s_classRegistered)
        {
            WNDCLASSEXW wc   = {};
            wc.cbSize        = sizeof(WNDCLASSEXW);
            wc.style         = CS_HREDRAW | CS_VREDRAW;
            wc.lpfnWndProc   = WndProc;
            wc.hInstance     = hInstance;
            wc.hCursor       = LoadCursor(nullptr, IDC_ARROW);
            wc.hbrBackground = static_cast<HBRUSH>(GetStockObject(BLACK_BRUSH));
            wc.lpszClassName = WINDOW_CLASS_NAME;

            if (!RegisterClassExW(&wc))
            {
                return false;
            }
            s_classRegistered = true;
        }

        // 창 크기 조정
        RECT  rect  = {0, 0, width, height};
        DWORD style = WS_OVERLAPPEDWINDOW;
        AdjustWindowRect(&rect, style, FALSE);

        int32 windowWidth  = rect.right - rect.left;
        int32 windowHeight = rect.bottom - rect.top;

        // 화면 크기 조정
        int32 screenWidth  = GetSystemMetrics(SM_CXSCREEN);
        int32 screenHeight = GetSystemMetrics(SM_CYSCREEN);
        int32 posX         = (screenWidth - windowWidth) / 2;
        int32 posY         = (screenHeight - windowHeight) / 2;

        // Title 변환
        wstring wideTitle = ToWideString(title);

        // 창 생성
        m_hWnd = CreateWindowExW(
            0,
            WINDOW_CLASS_NAME,
            wideTitle.c_str(),
            style,
            posX, posY,
            windowWidth, windowHeight,
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
        UpdateWindow(m_hWnd);

        return true;
    }

    void Win32Window::SetTitle(const char* title)
    {
        wstring wideTitle = ToWideString(title);
        SetWindowTextW(m_hWnd, wideTitle.c_str());
    }

    void Win32Window::PollEvents()
    {
        MSG msg = {};
        while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
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

    LRESULT CALLBACK Win32Window::WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
    {
        Win32Window* window = nullptr;

        if (msg == WM_NCCREATE)
        {
            // 창 생성 매개변수 설정
            CREATESTRUCTW* cs = reinterpret_cast<CREATESTRUCTW*>(lParam);
            window            = static_cast<Win32Window*>(cs->lpCreateParams);
            SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(window));
        }
        else
        {
            window = reinterpret_cast<Win32Window*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));
        }

        switch (msg)
        {
        case WM_CLOSE:
            if (window)
            {
                window->m_isOpen = false;
            }
            return 0;

        case WM_SIZE:
            if (window)
            {
                window->m_width  = LOWORD(lParam);
                window->m_height = HIWORD(lParam);
            }
            return 0;

        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;
        }

        return DefWindowProc(hWnd, msg, wParam, lParam);
    } // WndProc

    wstring Win32Window::ToWideString(const string& str)
    {
        if (str.empty())
        {
            return wstring();
        }

        int len = MultiByteToWideChar(CP_UTF8, 0, str.c_str(), static_cast<int>(str.size()), nullptr, 0);

        wstring wideStr(len, 0);
        MultiByteToWideChar(CP_UTF8, 0, str.c_str(), static_cast<int>(str.size()), wideStr.data(), len);

        return wideStr;
    } // ToWideString
} // namespace TDME
