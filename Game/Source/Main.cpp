#include "pch.h"

#include <Core/Math/MathConstants.h>
#include <Core/Math/TMatrix4x4.h>
#include <Core/Math/Projections.h>
#include <Core/Math/Transformations.h>
#include <Engine/ApplicationCore/IWindow.h>
#include <Engine/ApplicationCore/WindowDesc.h>
#include <Engine/Input/EKeys.h>
#include <Engine/Input/IInputDevice.h>
#include <Engine/RHI/State/IRasterizerState.h>
#include <Engine/RHI/State/IBlendState.h>
#include <Engine/RHI/State/IDepthStencilState.h>
#include <Engine/RHI/State/Rasterizer/ECullMode.h>
#include <Engine/RHI/State/Rasterizer/EFillMode.h>
#include <Engine/RHI/State/Rasterizer/RasterizerStateDesc.h>
#include <Engine/RHI/SwapChain/SwapChainDesc.h>
#include <Engine/Renderer/Shape/Shape3DRenderer.h>
#include <Platform_Windows/Win32Application.h>
#include <Platform_Windows/Time/Win32Timer.h>
#include <Platform_Windows/Input/Win32Input.h>
#include <Renderer_DX9/DX9Renderer.h>
#include <Renderer_DX9/DX9Device.h>

#include "Game/Types/Color.h"
#include "Game/Object/Actor/APlanet.h"
#include <memory>

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

    constexpr TDME::EFillMode fillModes[] = {TDME::EFillMode::Solid, TDME::EFillMode::Wireframe};
    constexpr TDME::ECullMode cullModes[] = {TDME::ECullMode::None, TDME::ECullMode::Back, TDME::ECullMode::Front};
    constexpr int             FILL_COUNT  = 2;
    constexpr int             CULL_COUNT  = 3;

    int fillIndex = 0;
    int cullIndex = 0;

    std::unique_ptr<TDME::IRasterizerState> rsStates[FILL_COUNT][CULL_COUNT];
    for (int i = 0; i < FILL_COUNT; i++)
    {
        for (int j = 0; j < CULL_COUNT; j++)
        {
            TDME::RasterizerStateDesc rsDesc;
            rsDesc.FillMode = fillModes[i];
            rsDesc.CullMode = cullModes[j];
            rsStates[i][j]  = device.CreateRasterizerState(rsDesc);
        }
    }

    TDME::BlendStateDesc bsDesc;
    bsDesc.BlendEnable = false;
    auto blendState    = device.CreateBlendState(bsDesc);

    TDME::DepthStencilStateDesc dsDesc;
    dsDesc.DepthEnable      = true;
    dsDesc.DepthWriteEnable = true;
    dsDesc.DepthFunc        = TDME::EComparisonFunc::Less;
    auto depthStencilState  = device.CreateDepthStencilState(dsDesc);

    renderer.SetRasterizerState(rsStates[fillIndex][cullIndex].get());
    renderer.SetBlendState(blendState.get());
    renderer.SetDepthStencilState(depthStencilState.get());

    // 투영 행렬 설정 (원근 투영)
    constexpr float fovY           = TDME::Math::Pi / 3.0f; // 60도
    constexpr float cameraDistance = 500.0f;
    float           aspect         = static_cast<float>(windowDesc.Width) / static_cast<float>(windowDesc.Height);

    TDME::Matrix projection = TDME::PerspectiveFovLH(fovY, aspect, 0.1f, 1000.0f);
    renderer.SetProjectionMatrix(projection);

    // 카메라 설정
    TDME::Vector3   cameraPosition(0.0f, 0.0f, -cameraDistance);
    TDME::Vector3   cameraTarget(0.0f, 0.0f, 0.0f);
    TDME::Vector3   cameraUp(0.0f, 1.0f, 0.0f); // 영속 up 벡터 (프레임 간 유지)
    constexpr float cameraMoveSpeed = 200.0f;   // 초당 이동 속도

    // 5. Timer 생성
    TDME::Win32Timer timer;
    timer.Reset();

    TDME::IInputDevice* input = application.GetInput();

    // 6. Shape3DRenderer 생성
    TDME::Shape3DRenderer shape3D(&renderer, &device);

    TDME::APlanet sun;
#pragma region 속도 및 반경 설정
    sun.SetColor(TDME::Colors::YELLOW);
    sun.SetBodyRadius(50.0f);
    sun.SetSpinSpeed(0.5f);
#pragma endregion

    TDME::APlanet earth;
#pragma region 속도 및 반경 설정
    earth.SetColor(TDME::Colors::AQUA);
    earth.SetOrbitRadius(200.0f);
    earth.SetBodyRadius(20.0f);
    earth.SetSpinSpeed(3.0f);
#pragma endregion
    earth.SetOrbitSpeed(1.0f);

    TDME::APlanet moon;
#pragma region 속도 및 반경 설정
    moon.SetColor(TDME::Colors::WHITE);
    moon.SetOrbitRadius(50.0f);
    moon.SetBodyRadius(8.0f);
    moon.SetSpinSpeed(0.0f);
#pragma endregion
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
        // 렌더링 상태 변경
        //////////////////////////////////////////////////////////////
        if (input->IsKeyPressed(TDME::EKeys::F1))
        {
            fillIndex = (fillIndex + 1) % FILL_COUNT;
            renderer.SetRasterizerState(rsStates[fillIndex][cullIndex].get());
        }
        if (input->IsKeyPressed(TDME::EKeys::F2))
        {
            cullIndex = (cullIndex + 1) % CULL_COUNT;
            renderer.SetRasterizerState(rsStates[fillIndex][cullIndex].get());
        }

        //////////////////////////////////////////////////////////////
        // 카메라 이동 (WASD + QE)
        //////////////////////////////////////////////////////////////
        TDME::Vector3 forward = (cameraTarget - cameraPosition).Normalized();

        // cameraUp × forward로 right 계산
        TDME::Vector3 right    = cameraUp.Cross(forward);
        float         rightLen = right.Length();

        if (rightLen > 0.001f)
        {
            right    = right / rightLen;
            cameraUp = forward.Cross(right);
        }

        TDME::Vector3 up = cameraUp;

        float moveStep = cameraMoveSpeed * deltaTime;

        if (input->IsKeyDown(TDME::EKeys::W))
            cameraPosition = cameraPosition + forward * moveStep;
        if (input->IsKeyDown(TDME::EKeys::S))
            cameraPosition = cameraPosition - forward * moveStep;
        if (input->IsKeyDown(TDME::EKeys::A))
            cameraPosition = cameraPosition - right * moveStep;
        if (input->IsKeyDown(TDME::EKeys::D))
            cameraPosition = cameraPosition + right * moveStep;
        if (input->IsKeyDown(TDME::EKeys::Q))
            cameraPosition = cameraPosition + up * moveStep;
        if (input->IsKeyDown(TDME::EKeys::E))
            cameraPosition = cameraPosition - up * moveStep;

        // 뷰 행렬 매 프레임 갱신
        TDME::Matrix view = TDME::LookAtLH(cameraPosition, cameraTarget, cameraUp);
        renderer.SetViewMatrix(view);

        //////////////////////////////////////////////////////////////
        // 게임 Update 로직
        //////////////////////////////////////////////////////////////
        // DEBUG: 태양계 테스트
        sun.Update(deltaTime);
        earth.Update(deltaTime);
        moon.Update(deltaTime);

        //////////////////////////////////////////////////////////////
        // 렌더링 시작 ----->
        //////////////////////////////////////////////////////////////
        // DEBUG: 회색 배경 테스트
        renderer.BeginFrame(TDME::Colors::DARK_GRAY);

        // TODO: Render 렌더링
        // DEBUG: 태양계 그리기
        sun.Render(shape3D);
        earth.Render(shape3D);
        moon.Render(shape3D);

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
