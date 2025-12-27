#include "pch.h"

#include <Platform_Windows/Win32Window.h>
#include <Renderer_DX9/DX9Renderer.h>

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine,
                   _In_ int nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // 1. Window 생성 (생성 실패시 MessageBox 출력 후 종료)
    TDME::Win32Window window;

    if (!window.Create(1280, 720, "TDME Engine"))
    {
        MessageBoxA(nullptr, "Failed to create window", "Error", MB_OK | MB_ICONERROR);
        return -1;
    }

    // 2. Renderer 생성
    TDME::DX9Renderer renderer;
    if (!renderer.Initialize(&window))
    {
        MessageBoxA(nullptr, "Failed to create renderer", "Error", MB_OK | MB_ICONERROR);
        return -1;
    }

    // Main loop
    while (window.IsOpen())
    {
        window.PollEvents();

        // TODO: Update 게임 로직

        //////////////////////////////////////////////////////////////
        // Frame 시작
        //////////////////////////////////////////////////////////////

        // DEBUG: 시안 배경 테스트
        renderer.BeginFrame(TDME::Colors::CYAN);

        // TODO: Render 렌더링

        renderer.EndFrame();

        //////////////////////////////////////////////////////////////
        // Frame 종료
        //////////////////////////////////////////////////////////////
    }

    renderer.Shutdown();
    return 0;
}
