#include "pch.h"
#include "Platform_Windows/Win32Application.h"

#include <Engine/ApplicationCore/WindowDesc.h>

#include "Platform_Windows/Input/Win32Input.h"
#include "Platform_Windows/Window/Win32Window.h"
#include <algorithm>
#include <minwindef.h>
#include <winuser.h>

namespace TDME
{
    static constexpr const WCHAR* WINDOW_CLASS_NAME = L"TDME_WindowClass";

    Win32Application* Win32Application::s_instance        = nullptr;
    bool              Win32Application::s_classRegistered = false;

    Win32Application::Win32Application()
        : m_input(std::make_unique<Win32Input>())
    {
        s_instance = this;
        RegisterWindowClass();
    }

    Win32Application::~Win32Application()
    {
        s_instance = nullptr;
    }

    void Win32Application::ProcessMessages()
    {
        MSG msg = {};
        while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
        {
            if (msg.message == WM_QUIT)
            {
                m_quitRequested = true;
                m_exitCode      = static_cast<int32>(msg.wParam);
                return;
            }

            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    IWindow* Win32Application::MakeWindow(const WindowDesc& windowDesc)
    {
        std::unique_ptr<Win32Window> window = std::make_unique<Win32Window>();
        if (!window->Create(static_cast<int32>(windowDesc.Width), static_cast<int32>(windowDesc.Height), windowDesc.Title.c_str()))
        {
            return nullptr;
        }

        Win32Window* result = window.get();
        m_windows.push_back(std::move(window));
        return result;
    }

    void Win32Application::DestroyWindow(IWindow* window)
    {
        auto it = std::find_if(m_windows.begin(), m_windows.end(),
                               [window](const std::unique_ptr<Win32Window>& win)
                               { return win.get() == window; }); // 윈도우 포인터를 통해 윈도우 찾기

        if (it != m_windows.end())
        {
            m_windows.erase(it);
        }
    }

    void Win32Application::RequestQuit(int32 exitCode)
    {
        m_quitRequested = true;
        m_exitCode      = exitCode;
        PostQuitMessage(exitCode);
    }

    //////////////////////////////////////////////////////////////
    // Win32 Application 관리
    //////////////////////////////////////////////////////////////

    LRESULT Win32Application::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
    {
        if (!s_instance)
        {
            return DefWindowProc(hWnd, message, wParam, lParam); // Windows 기본 동작으로 메시지 처리를 넘김
        }

        LRESULT result = 0;

        if (message == WM_NCCREATE) // 윈도우 생성시
        {
            CREATESTRUCTW* cs = reinterpret_cast<CREATESTRUCTW*>(lParam);
            SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(cs->lpCreateParams)); // 윈도우에 사용자 데이터를 저장
        }

        // 입력 메시지 처리
        if (s_instance->m_input)
        {
            s_instance->m_input->ProcessMessage(hWnd, message, wParam, lParam, result);
        }

        // 윈도우 메시지 처리
        Win32Window* window = s_instance->FindWindowByHandle(hWnd);
        if (window && window->ProcessMessage(hWnd, message, wParam, lParam, result))
        {
            return result;
        }

        return DefWindowProc(hWnd, message, wParam, lParam); // Windows 기본 동작으로 메시지 처리를 넘김
    }

    //////////////////////////////////////////////////////////////
    // Getter / Setter
    //////////////////////////////////////////////////////////////

    void Win32Application::SetMessageHandler(IApplicationMessageHandler* messageHandler)
    {
        m_messageHandler = messageHandler;
    }

    bool Win32Application::IsQuitRequested() const
    {
        return m_quitRequested;
    }

    int32 Win32Application::GetExitCode() const
    {
        return m_exitCode;
    }

    //////////////////////////////////////////////////////////////
    // Private Functions
    //////////////////////////////////////////////////////////////

    bool Win32Application::RegisterWindowClass()
    {
        if (s_classRegistered)
        {
            return true;
        }

        HINSTANCE hInstance = GetModuleHandle(nullptr);

        WNDCLASSEXW wcex   = {};
        wcex.lpszClassName = WINDOW_CLASS_NAME;
        wcex.hInstance     = hInstance;
        wcex.lpfnWndProc   = WndProc;
        wcex.hbrBackground = static_cast<HBRUSH>(GetStockObject(BLACK_BRUSH));
        wcex.hCursor       = LoadCursor(nullptr, IDC_ARROW);
        wcex.style         = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
        wcex.cbSize        = sizeof(WNDCLASSEXW);
        wcex.lpszMenuName  = nullptr;
        wcex.hIcon         = nullptr;
        wcex.hIconSm       = nullptr;
        wcex.cbClsExtra    = 0; // 프로그램 추가 확장 메모리 구역
        wcex.cbWndExtra    = 0; // Window 추가 확장 메모리 구역

        if (!RegisterClassExW(&wcex))
        {
            return false;
        }

        s_classRegistered = true;
        return true;
    }

    Win32Window* Win32Application::FindWindowByHandle(HWND hWnd) const
    {
        auto it = std::find_if(m_windows.begin(), m_windows.end(),
                               [hWnd](const std::unique_ptr<Win32Window>& w)
                               { return w->GetHWnd() == hWnd; }); // 윈도우 핸들을 통해 윈도우 찾기

        return (it != m_windows.end()) ? it->get() : nullptr;
    }

} // namespace TDME