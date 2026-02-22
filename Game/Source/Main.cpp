#include "pch.h"

#include <Core/Math/MathConstants.h>
#include <Core/IO/FileUtility.h>
#include <Core/Image/BMPLoader.h>
#include <Core/Image/ImageData.h>
#include <Core/Types/Color.h>
#include <Engine/ApplicationCore/IWindow.h>
#include <Engine/EngineContext.h>
#include <Engine/Input/EKeys.h>
#include <Engine/RHI/IRHIDevice.h>
#include <Engine/RHI/State/IRasterizerState.h>
#include <Engine/RHI/State/IBlendState.h>
#include <Engine/RHI/State/IDepthStencilState.h>
#include <Engine/RHI/State/Rasterizer/ECullMode.h>
#include <Engine/RHI/State/Rasterizer/EFillMode.h>
#include <Engine/RHI/State/Rasterizer/RasterizerStateDesc.h>
#include <Engine/RHI/Texture/ETextureFormat.h>
#include <Engine/RHI/Texture/ITexture.h>
#include <Engine/RHI/Texture/TextureDesc.h>
#include <Engine/Renderer/Shape/Shape3DRenderer.h>
#include <Engine/World/World.h>
#include <Engine/Object/Component/GCameraComponent.h>

#include "Game/Factory/Win32DX9Factory.h"
#include "Game/Object/Actor/APlanet.h"
#include <memory>

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine,
                   _In_ int nCmdShow)
{
    UNREFERENCED_PARAMETER(hInstance);
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);
    UNREFERENCED_PARAMETER(nCmdShow);

    // 1. Engine 생성 (팩토리 사용)
    TDME::EngineDesc desc;
    desc.Window.Title              = "테스트 윈도우";
    desc.Window.Width              = 1280;
    desc.Window.Height             = 720;
    desc.SwapChain.BackBufferCount = 1;
    desc.SwapChain.VSync           = true;

    TDME::EngineContext engine = TDME::CreateWin32DX9Engine(desc);
    if (!engine.IsValid())
    {
        MessageBoxA(nullptr, "Failed to create engine", "Error", MB_OK | MB_ICONERROR);
        return -1;
    }

    // 2. Render State 생성
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
            rsStates[i][j]  = engine.Device->CreateRasterizerState(rsDesc);
        }
    }

    TDME::BlendStateDesc bsDesc;
    bsDesc.BlendEnable = false;
    auto blendState    = engine.Device->CreateBlendState(bsDesc);

    TDME::DepthStencilStateDesc dsDesc;
    dsDesc.DepthEnable      = true;
    dsDesc.DepthWriteEnable = true;
    dsDesc.DepthFunc        = TDME::EComparisonFunc::Less;
    auto depthStencilState  = engine.Device->CreateDepthStencilState(dsDesc);

    engine.Renderer->SetRasterizerState(rsStates[fillIndex][cullIndex].get());
    engine.Renderer->SetBlendState(blendState.get());
    engine.Renderer->SetDepthStencilState(depthStencilState.get());

    // 3. Camera 설정
    TDME::GCameraComponent camera;

    constexpr float fovY   = TDME::Math::Pi / 3.0f;
    float           aspect = static_cast<float>(engine.Window->GetWidth()) / static_cast<float>(engine.Window->GetHeight());
    camera.SetPerspective(fovY, aspect, 0.1f, 1000.0f);
    camera.SetPosition(TDME::Vector3(0.f, 0.f, -500.f));
    engine.Renderer->SetProjectionMatrix(camera.GetProjectionMatrix());

    constexpr float cameraMoveSpeed   = 200.0f;
    constexpr float cameraRotateSpeed = 1.5f;

    // 4. Shape3DRenderer 생성
    TDME::Shape3DRenderer shape3D(engine.Renderer.get(), engine.Device.get());

    // 5. Texture 로딩
    auto LoadTexture = [&engine](const char* path) -> std::unique_ptr<TDME::ITexture>
    {
        auto fileData = TDME::FileUtility::ReadBinaryFile(path);
        if (!fileData)
            return nullptr;

        auto imageData = TDME::BMPLoader::Load(*fileData);
        if (!imageData)
            return nullptr;

        TDME::TextureDesc texDesc;
        texDesc.Width     = imageData->Width;
        texDesc.Height    = imageData->Height;
        texDesc.MipLevels = 1;
        texDesc.Format    = TDME::ETextureFormat::R8G8B8A8;

        return engine.Device->CreateTexture(texDesc, imageData->Pixels.data());
    };

    auto sunTexture   = LoadTexture("Assets/Textures/sun.bmp");
    auto earthTexture = LoadTexture("Assets/Textures/earth.bmp");
    auto moonTexture  = LoadTexture("Assets/Textures/moon.bmp");

    //////////////////////////////////////////////////////////////
    // 6. 행성 생성
    //////////////////////////////////////////////////////////////

    TDME::World world;

    auto* sun = world.SpawnActor<TDME::APlanet>();
    sun->SetRenderer(&shape3D);
#pragma region 속도 및 반경 설정
    sun->SetColor(TDME::Colors::YELLOW);
    sun->SetBodyRadius(50.0f);
    sun->SetSpinSpeed(0.5f);
    if (sunTexture)
        sun->SetTexture(sunTexture.get());
#pragma endregion

    auto* earth = world.SpawnActor<TDME::APlanet>();
    earth->SetRenderer(&shape3D);
#pragma region 속도 및 반경 설정
    earth->SetColor(TDME::Colors::CYAN);
    earth->SetOrbitRadius(200.0f);
    earth->SetBodyRadius(20.0f);
    earth->SetSpinSpeed(3.0f);
    if (earthTexture)
        earth->SetTexture(earthTexture.get());
#pragma endregion
    earth->SetOrbitSpeed(1.0f);

    auto* moon = world.SpawnActor<TDME::APlanet>();
    moon->SetRenderer(&shape3D);
#pragma region 속도 및 반경 설정
    moon->SetColor(TDME::Colors::WHITE);
    moon->SetOrbitRadius(50.0f);
    moon->SetBodyRadius(8.0f);
    moon->SetSpinSpeed(0.0f);
    if (moonTexture)
        moon->SetTexture(moonTexture.get());
#pragma endregion
    moon->SetOrbitSpeed(2.5f);

    earth->OrbitAround(sun);
    moon->OrbitAround(earth);

    // Main loop
    while (!engine.Application->IsQuitRequested() && engine.Window->IsOpen())
    {
        //////////////////////////////////////////////////////////////
        // 시간 관련 로직
        //////////////////////////////////////////////////////////////
        engine.Timer->Tick();
        float deltaTime = engine.Timer->GetDeltaTime();

        //////////////////////////////////////////////////////////////
        // 입력 및 이벤트 처리
        //////////////////////////////////////////////////////////////
        engine.Input->Update();
        engine.Application->ProcessMessages();

        //////////////////////////////////////////////////////////////
        // 렌더링 상태 변경
        //////////////////////////////////////////////////////////////
        if (engine.Input->IsKeyPressed(TDME::EKeys::F1))
        {
            fillIndex = (fillIndex + 1) % FILL_COUNT;
            engine.Renderer->SetRasterizerState(rsStates[fillIndex][cullIndex].get());
        }
        if (engine.Input->IsKeyPressed(TDME::EKeys::F2))
        {
            cullIndex = (cullIndex + 1) % CULL_COUNT;
            engine.Renderer->SetRasterizerState(rsStates[fillIndex][cullIndex].get());
        }

        //////////////////////////////////////////////////////////////
        // 카메라 입력
        //////////////////////////////////////////////////////////////
        float moveStep   = cameraMoveSpeed * deltaTime;
        float rotateStep = cameraRotateSpeed * deltaTime;

        // 이동: WASD(상하좌우) + ZX(전후)
        if (engine.Input->IsKeyDown(TDME::EKeys::W))
            camera.MoveUp(moveStep);
        if (engine.Input->IsKeyDown(TDME::EKeys::S))
            camera.MoveUp(-moveStep);
        if (engine.Input->IsKeyDown(TDME::EKeys::A))
            camera.MoveRight(-moveStep);
        if (engine.Input->IsKeyDown(TDME::EKeys::D))
            camera.MoveRight(moveStep);
        if (engine.Input->IsKeyDown(TDME::EKeys::Z))
            camera.MoveForward(moveStep);
        if (engine.Input->IsKeyDown(TDME::EKeys::X))
            camera.MoveForward(-moveStep);

        // 회전: 화살표(Yaw/Pitch) + QE(Roll)
        if (engine.Input->IsKeyDown(TDME::EKeys::Left))
            camera.RotateYaw(-rotateStep);
        if (engine.Input->IsKeyDown(TDME::EKeys::Right))
            camera.RotateYaw(rotateStep);
        if (engine.Input->IsKeyDown(TDME::EKeys::Up))
            camera.RotatePitch(-rotateStep);
        if (engine.Input->IsKeyDown(TDME::EKeys::Down))
            camera.RotatePitch(rotateStep);
        if (engine.Input->IsKeyDown(TDME::EKeys::Q))
            camera.RotateRoll(-rotateStep);
        if (engine.Input->IsKeyDown(TDME::EKeys::E))
            camera.RotateRoll(rotateStep);

        engine.Renderer->SetViewMatrix(camera.GetViewMatrix());

        //////////////////////////////////////////////////////////////
        // 게임 Update 로직
        //////////////////////////////////////////////////////////////
        world.Update(deltaTime);

        //////////////////////////////////////////////////////////////
        // 렌더링 시작 ----->
        //////////////////////////////////////////////////////////////
        engine.Renderer->BeginFrame(TDME::Colors::DARK_GRAY); // DEBUG: 회색 배경 테스트
        world.Render();
        engine.Renderer->EndFrame();
        engine.Device->Present();
        //////////////////////////////////////////////////////////////
        // <----- 렌더링 종료
        //////////////////////////////////////////////////////////////
    }

    engine.Renderer->Shutdown();
    engine.Device->Shutdown();
    return engine.Application->GetExitCode();
}
