#include "pch.h"

#include <Core/Types/Color.h>
#include <Core/Math/TVector2.h>
#include <Core/Math/TMatrix4x4.h>
#include <Core/Math/Projections.h>
#include <Engine/ApplicationCore/IWindow.h>
#include <Engine/ApplicationCore/WindowDesc.h>
#include <Engine/Input/EKeys.h>
#include <Engine/Input/IInputDevice.h>
#include <Engine/RHI/SwapChain/SwapChainDesc.h>
#include <Engine/Renderer/Shape/Shape2DRenderer.h>
#include <Platform_Windows/Win32Application.h>
#include <Platform_Windows/Time/Win32Timer.h>
#include <Platform_Windows/Input/Win32Input.h>
#include <Renderer_DX9/DX9Renderer.h>
#include <Renderer_DX9/DX9Device.h>

#include "Game/Types/Color.h"
#include "Game/Object/Actor/APlanet.h"

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine,
                   _In_ int nCmdShow)
{
    UNREFERENCED_PARAMETER(hInstance);
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);
    UNREFERENCED_PARAMETER(nCmdShow);

    // 1. Application 생성
    TDME::Win32Application application;

    // 2. Window 생성 (생성 실패시 MessageBox 출력 후 종료)
    TDME::WindowDesc windowDesc;
    windowDesc.Title  = "테스트 윈도우";
    windowDesc.Width  = 1280;
    windowDesc.Height = 720;

    TDME::IWindow* window = application.MakeWindow(windowDesc);
    if (!window)
    {
        MessageBoxA(nullptr, "Failed to create window", "Error", MB_OK | MB_ICONERROR);
        return -1;
    }

    // 3. Device 생성
    TDME::SwapChainDesc swapChainDesc;
    swapChainDesc.BackBufferCount = 1;
    swapChainDesc.VSync           = true;

    TDME::DX9Device device;
    if (!device.Initialize(window, swapChainDesc))
    {
        MessageBoxA(nullptr, "Failed to create device", "Error", MB_OK | MB_ICONERROR);
        return -1;
    }

    // 4. Renderer 생성
    TDME::DX9Renderer renderer;
    renderer.SetDevice(&device);
    if (!renderer.Initialize(window))
    {
        MessageBoxA(nullptr, "Failed to create renderer", "Error", MB_OK | MB_ICONERROR);
        return -1;
    }

    // DEBUG: 임시 투영 행렬 설정
    TDME::Matrix projection = TDME::Orthographic2DCentered(1280.0f, 720.0f);
    renderer.SetProjectionMatrix(projection);
    renderer.SetViewMatrix(TDME::Matrix::Identity());

    // 5. Timer 생성
    TDME::Win32Timer timer;
    timer.Reset();

    TDME::IInputDevice* input = application.GetInput();

    // 6. Shape2DRenderer 생성 (DEBUG: 삼각형 테스트)
    TDME::Shape2DRenderer shape2D(&renderer, &device);

    TDME::APlanet sun;
    sun.SetColor(TDME::Colors::YELLOW);
    sun.SetBodyRadius(50.0f);
    sun.SetSpinSpeed(0.5f);

    TDME::APlanet earth;
    earth.SetColor(TDME::Colors::AQUA);
    earth.SetOrbitRadius(200.0f);
    earth.SetBodyRadius(20.0f);
    earth.SetSpinSpeed(3.0f);
    earth.SetOrbitSpeed(1.0f);

    TDME::APlanet moon;
    moon.SetColor(TDME::Colors::WHITE);
    moon.SetOrbitRadius(50.0f);
    moon.SetBodyRadius(8.0f);
    moon.SetSpinSpeed(0.0f);
    moon.SetOrbitSpeed(2.5f);

    earth.OrbitAround(&sun);
    moon.OrbitAround(&earth);

    // Main loop
    while (!application.IsQuitRequested() && window->IsOpen())
    {
        //////////////////////////////////////////////////////////////
        // 시간 관련 로직
        //////////////////////////////////////////////////////////////
        timer.Tick();
        float deltaTime = timer.GetDeltaTime();
        //////////////////////////////////////////////////////////////
        // 입력 및 이벤트 처리
        //////////////////////////////////////////////////////////////
        input->Update();
        application.ProcessMessages();
        //////////////////////////////////////////////////////////////
        // 게임 Update 로직
        //////////////////////////////////////////////////////////////
        // TODO: Update 게임 로직
        // DEBUG: 태양계 테스트
        sun.Update(deltaTime);
        earth.Update(deltaTime);
        moon.Update(deltaTime);

        // 마우스 위치
        TDME::Vector2 mousePosition = input->GetAxis2D(TDME::EKeys::Mouse2D);

        //////////////////////////////////////////////////////////////
        // 렌더링 시작 ----->
        //////////////////////////////////////////////////////////////
        // DEBUG: 회색 배경 테스트
        renderer.BeginFrame(TDME::Colors::DARK_GRAY);

        // TODO: Render 렌더링
        // DEBUG: 태양계 그리기
        sun.Render(shape2D);
        earth.Render(shape2D);
        moon.Render(shape2D);

        renderer.EndFrame();
        device.Present();
        //////////////////////////////////////////////////////////////
        // <----- 렌더링 종료
        //////////////////////////////////////////////////////////////
    }

    renderer.Shutdown();
    device.Shutdown();
    return application.GetExitCode();
}
