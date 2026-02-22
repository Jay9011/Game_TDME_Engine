#include "pch.h"
#include "Game/Factory/Win32DX9Factory.h"

#include <Platform_Windows/Win32Application.h>
#include <Platform_Windows/Input/Win32Input.h>
#include <Platform_Windows/Time/Win32Timer.h>
#include <Renderer_DX9/DX9Device.h>
#include <Renderer_DX9/DX9Renderer.h>

namespace TDME
{
    EngineContext CreateWin32DX9Engine(const EngineDesc& desc)
    {
        EngineContext context;

        // 1. Application + Window 생성
        std::unique_ptr<Win32Application> app = std::make_unique<Win32Application>();

        IWindow* window = app->MakeWindow(desc.Window);

        if (!window)
            return context;

        context.Window      = window;
        context.Input       = app->GetInput();
        context.Application = std::move(app);

        // 2. Device 생성 및 초기화
        std::unique_ptr<DX9Device> device = std::make_unique<DX9Device>();

        if (!device->Initialize(window, desc.SwapChain))
            return context;

        // 3. Renderer 생성 + Deivce 연걸
        std::unique_ptr<DX9Renderer> renderer = std::make_unique<DX9Renderer>();
        renderer->SetDevice(device.get());

        if (!renderer->Initialize(window))
            return context;

        context.Device   = std::move(device);
        context.Renderer = std::move(renderer);

        // 4. Timer 생성
        context.Timer = std::make_unique<Win32Timer>();
        context.Timer->Reset();

        return context;
    }
} // namespace TDME
