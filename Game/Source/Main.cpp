#include "pch.h"

#include <Core/Types/Color.h>
#include <Core/Math/TVector2.h>
#include <Core/Math/TMatrix4x4.h>
#include <Core/Math/Detail/TMatrix4x4.Projection2D.h>
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
    TDME::Matrix4 projection = TDME::Orthographic2D(1280.0f, 720.0f);
    renderer.SetProjectionMatrix(projection);
    renderer.SetViewMatrix(TDME::Matrix::IDENTITY);

    // 5. Timer 생성
    TDME::Win32Timer timer;
    timer.Reset();

    TDME::IInputDevice* input = application.GetInput();

    // 6. Shape2DRenderer 생성 (DEBUG: 삼각형 테스트)
    TDME::Shape2DRenderer shape2D(&renderer, &device);

    float       rotation      = 0.0f;
    float       width         = 100.0f;
    float       height        = 100.0f;
    TDME::Color triangleColor = TDME::Colors::WHITE;

    constexpr float ROTATION_SPEED = 180.0f; // 1초에 180도 회전
    constexpr float SIZE_SPEED     = 100.0f; // 1초에 100픽셀 이동

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
        // DEBUG: 입력 테스트
        // 색상 변경
        if (input->IsKeyPressed(TDME::EKeys::W))
            triangleColor = TDME::Colors::WHITE;
        if (input->IsKeyPressed(TDME::EKeys::A))
            triangleColor = TDME::Colors::AQUA;
        if (input->IsKeyPressed(TDME::EKeys::S))
            triangleColor = TDME::Colors::SAGE_GREEN;
        if (input->IsKeyPressed(TDME::EKeys::D))
            triangleColor = TDME::Colors::DARK_VIOLET;
        // 회전 (Space를 누르고 있는 동안)
        if (input->IsKeyDown(TDME::EKeys::SpaceBar))
            rotation += ROTATION_SPEED * deltaTime;
        // 크기 조절 (화살표를 누르고 있는 동안)
        if (input->IsKeyDown(TDME::EKeys::Up))
            height += SIZE_SPEED * deltaTime;
        if (input->IsKeyDown(TDME::EKeys::Down))
            height -= SIZE_SPEED * deltaTime;
        if (input->IsKeyDown(TDME::EKeys::Left))
            width -= SIZE_SPEED * deltaTime;
        if (input->IsKeyDown(TDME::EKeys::Right))
            width += SIZE_SPEED * deltaTime;
        // 크기 최소값 제한
        width  = std::max<float>(width, 10.0f);
        height = std::max<float>(height, 10.0f);
        // 마우스 위치
        TDME::Vector2 mousePosition = input->GetAxis2D(TDME::EKeys::Mouse2D);

        //////////////////////////////////////////////////////////////
        // 렌더링 시작 ----->
        //////////////////////////////////////////////////////////////
        // DEBUG: 회색 배경 테스트
        renderer.BeginFrame(TDME::Colors::DARK_GRAY);

        // TODO: Render 렌더링
        // DEBUG: 삼각형 그리기
        shape2D.DrawTriangle(mousePosition, width, height, rotation, triangleColor);

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
