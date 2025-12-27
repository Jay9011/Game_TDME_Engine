#include "pch.h"

#include <Platform_Windows/Win32Window.h>

#include <sal.h>
#include <minwindef.h>
#include <winnt.h>

int APIENTRY WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine,
                     _In_ int nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    TDME::Win32Window window;

    if (!window.Create(1280, 720, u8"TDME Engine"))
    {
        MessageBoxA(nullptr, "Failed to create window", "Error", MB_OK | MB_ICONERROR);
        return -1;
    }

    // Main loop
    while (window.IsOpen())
    {
        window.PollEvents();

        // TODO: Update 게임 로직
        // TODO: Render 렌더링
    }

    return 0;
}
