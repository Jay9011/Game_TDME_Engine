#include "pch.h"

#include <Core/IO/FileUtility.h>
#include <Core/Image/BMPLoader.h>
#include <Core/Image/ImageData.h>
#include <Engine/EngineContext.h>
#include <Engine/RHI/Pipeline/IPipelineState.h>
#include <Engine/RHI/Texture/ITexture.h>
#include <Engine/Renderer/VertexTypes.h>
#include <Engine/Renderer/Shape/Shape3DRenderer.h>
#include <Engine/World/World.h>
#include <Engine/Object/Component/GCameraComponent.h>

#include "Game/Factory/Win32DX9Factory.h"
#include "Game/Factory/Win32DX11Factory.h"
#include "Game/Object/Actor/APlanet.h"

#include <d3dcompiler.h> // NOTE: 임시
#pragma comment(lib, "d3dcompiler.lib")

#include <wrl/client.h>
using Microsoft::WRL::ComPtr;

/**
 * @brief HLSL 셰이더 컴파일
 * @param filePath 셰이더 파일 경로
 * @param entryPoint 셰이더 엔트리 포인트
 * @param target 셰이더 타겟
 * @return ComPtr<ID3DBlob> 컴파일된 셰이더 바이트코드
 */
static ComPtr<ID3DBlob> CompileShader(const wchar_t* filePath, const char* entryPoint, const char* target)
{
    ComPtr<ID3DBlob> blob;
    ComPtr<ID3DBlob> errorBlob;

    UINT flags = 0;
#ifdef _DEBUG
    flags |= D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION;
#endif

    HRESULT hr = D3DCompileFromFile(filePath, nullptr, nullptr, entryPoint, target, flags, 0, blob.GetAddressOf(), errorBlob.GetAddressOf());
    if (FAILED(hr))
    {
        if (errorBlob)
        {
            OutputDebugStringA(static_cast<const char*>(errorBlob->GetBufferPointer()));
        }
        return nullptr;
    }
    return blob;
};

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine,
                   _In_ int nCmdShow)
{
    UNREFERENCED_PARAMETER(hInstance);
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);
    UNREFERENCED_PARAMETER(nCmdShow);

    //////////////////////////////////////////////////////////////
    // Engine 생성 (팩토리 사용)
    //////////////////////////////////////////////////////////////
    TDME::EngineDesc desc;
    desc.Window.Title              = "테스트 윈도우";
    desc.Window.Width              = 1280;
    desc.Window.Height             = 720;
    desc.SwapChain.BackBufferCount = 1;
    desc.SwapChain.VSync           = true;

    // TDME::EngineContext engine = TDME::CreateWin32DX9Engine(desc); // DX9 엔진 사용
    TDME::EngineContext engine = TDME::CreateWin32DX11Engine(desc); // DX11 엔진 사용
    if (!engine.IsValid())
    {
        MessageBoxA(nullptr, "Failed to create engine", "Error", MB_OK | MB_ICONERROR);
        return -1;
    }

    //////////////////////////////////////////////////////////////
    // Shader 컴파일
    //////////////////////////////////////////////////////////////
    auto vsBlob = CompileShader(L"Assets/Shaders/Basic.hlsl", "VS_MAIN", "vs_5_0");
    auto psBlob = CompileShader(L"Assets/Shaders/Basic.hlsl", "PS_SOLID", "ps_5_0");
    if (!vsBlob || !psBlob)
    {
        MessageBoxA(nullptr, "Failed to compile shader", "Error", MB_OK | MB_ICONERROR);
        return -1;
    }

    //////////////////////////////////////////////////////////////
    // Shader 객체 생성
    //////////////////////////////////////////////////////////////
    auto vs = engine.Device->CreateVertexShader(vsBlob->GetBufferPointer(), vsBlob->GetBufferSize());
    auto ps = engine.Device->CreatePixelShader(psBlob->GetBufferPointer(), psBlob->GetBufferSize());
    if (!vs || !ps)
    {
        MessageBoxA(nullptr, "Failed to create shader", "Error", MB_OK | MB_ICONERROR);
        return -1;
    }

    //////////////////////////////////////////////////////////////
    // PSO 생성
    //////////////////////////////////////////////////////////////
    TDME::PipelineStateDesc psoDesc;
    psoDesc.VS = vs.get();
    psoDesc.PS = ps.get();
    psoDesc.InputLayout
        .Add(TDME::EVertexSemantic::Position, TDME::EVertexFormat::Float3)
        .Add(TDME::EVertexSemantic::TexCoord, TDME::EVertexFormat::Float2);
    psoDesc.RasterizerState.CullMode           = TDME::ECullMode::Back;
    psoDesc.DepthStencilState.DepthEnable      = true;
    psoDesc.DepthStencilState.DepthWriteEnable = true;

    auto pso = engine.Device->CreatePipelineState(psoDesc);
    if (!pso)
    {
        MessageBoxA(nullptr, "Failed to create pipeline state", "Error", MB_OK | MB_ICONERROR);
        return -1;
    }

    //////////////////////////////////////////////////////////////
    // Render State 생성
    //////////////////////////////////////////////////////////////
    constexpr TDME::EFillMode fillModes[] = {TDME::EFillMode::Solid, TDME::EFillMode::Wireframe};
    constexpr TDME::ECullMode cullModes[] = {TDME::ECullMode::None, TDME::ECullMode::Back, TDME::ECullMode::Front};
    constexpr int             FILL_COUNT  = 2;
    constexpr int             CULL_COUNT  = 3;

    int fillIndex = 0;
    int cullIndex = 0;

    std::unique_ptr<TDME::IPipelineState> psoStates[FILL_COUNT][CULL_COUNT];
    for (int i = 0; i < FILL_COUNT; i++)
    {
        for (int j = 0; j < CULL_COUNT; j++)
        {
            TDME::PipelineStateDesc psoDesc;

            psoDesc.VS = vs.get();
            psoDesc.PS = ps.get();
            psoDesc.InputLayout
                .Add(TDME::EVertexSemantic::Position, TDME::EVertexFormat::Float3)
                .Add(TDME::EVertexSemantic::TexCoord, TDME::EVertexFormat::Float2);

            // Rasterizer
            psoDesc.RasterizerState.FillMode = fillModes[i];
            psoDesc.RasterizerState.CullMode = cullModes[j];

            // DepthStencil
            psoDesc.DepthStencilState.DepthEnable      = true;
            psoDesc.DepthStencilState.DepthWriteEnable = true;
            psoDesc.DepthStencilState.DepthFunc        = TDME::EComparisonFunc::Less;

            psoStates[i][j] = engine.Device->CreatePipelineState(psoDesc);
        }
    }

    engine.Context->SetPipelineState(psoStates[fillIndex][cullIndex].get());

    //////////////////////////////////////////////////////////////
    // Camera 설정
    //////////////////////////////////////////////////////////////
    TDME::GCameraComponent camera;

    constexpr float fovY   = TDME::Math::Pi / 3.0f;
    float           aspect = static_cast<float>(engine.Window->GetWidth()) / static_cast<float>(engine.Window->GetHeight());
    camera.SetPerspective(fovY, aspect, 0.1f, 1000.0f);
    camera.SetPosition(TDME::Vector3(0.f, 0.f, -500.f));
    engine.Renderer->SetProjectionMatrix(camera.GetProjectionMatrix());

    constexpr float cameraMoveSpeed   = 200.0f;
    constexpr float cameraRotateSpeed = 1.5f;

    //////////////////////////////////////////////////////////////
    // 구체 메시 생성 (직접 렌더링 테스트)
    //////////////////////////////////////////////////////////////
    constexpr TDME::uint32 STACKS        = 16;
    constexpr TDME::uint32 SLICES        = 32;
    constexpr float        SPHERE_RADIUS = 50.0f;

    // 1. 정점 생성 (단위 구, radius = 1)
    std::vector<TDME::VertexPT> sphereVertices;
    sphereVertices.reserve((STACKS + 1) * (SLICES + 1));

    for (TDME::uint32 i = 0; i <= STACKS; i++)
    {
        float phi    = TDME::Math::Pi * static_cast<float>(i) / static_cast<float>(STACKS);
        float sinPhi = std::sin(phi);
        float cosPhi = std::cos(phi);

        for (TDME::uint32 j = 0; j <= SLICES; j++)
        {
            float theta    = TDME::Math::Pi2 * static_cast<float>(j) / static_cast<float>(SLICES);
            float sinTheta = std::sin(theta);
            float cosTheta = std::cos(theta);

            TDME::Vector3 pos(sinPhi * cosTheta, cosPhi, sinPhi * sinTheta);
            TDME::Vector2 uv(
                static_cast<float>(j) / static_cast<float>(SLICES),
                static_cast<float>(i) / static_cast<float>(STACKS));

            sphereVertices.emplace_back(pos, uv);
        }
    }

    // 2. 인덱스 생성
    TDME::uint32              indexCount = STACKS * SLICES * 6;
    std::vector<TDME::uint16> sphereIndices;
    sphereIndices.reserve(indexCount);

    for (TDME::uint32 i = 0; i < STACKS; i++)
    {
        for (TDME::uint32 j = 0; j < SLICES; j++)
        {
            TDME::uint16 topLeft     = static_cast<TDME::uint16>(i * (SLICES + 1) + j);
            TDME::uint16 topRight    = static_cast<TDME::uint16>(i * (SLICES + 1) + j + 1);
            TDME::uint16 bottomLeft  = static_cast<TDME::uint16>((i + 1) * (SLICES + 1) + j);
            TDME::uint16 bottomRight = static_cast<TDME::uint16>((i + 1) * (SLICES + 1) + j + 1);

            sphereIndices.push_back(topLeft);
            sphereIndices.push_back(topRight);
            sphereIndices.push_back(bottomLeft);

            sphereIndices.push_back(topRight);
            sphereIndices.push_back(bottomRight);
            sphereIndices.push_back(bottomLeft);
        }
    }

    // 3. GPU 버퍼 생성
    TDME::BufferDesc vbDesc;
    vbDesc.Type     = TDME::EBufferType::Vertex;
    vbDesc.Usage    = TDME::EBufferUsage::Default;
    vbDesc.ByteSize = static_cast<TDME::uint32>(sphereVertices.size() * sizeof(TDME::VertexPT));
    vbDesc.Stride   = sizeof(TDME::VertexPT);

    auto sphereVB = engine.Device->CreateBuffer(vbDesc, sphereVertices.data());

    TDME::BufferDesc ibDesc;
    ibDesc.Type     = TDME::EBufferType::Index;
    ibDesc.Usage    = TDME::EBufferUsage::Default;
    ibDesc.ByteSize = static_cast<TDME::uint32>(sphereIndices.size() * sizeof(TDME::uint16));
    ibDesc.Stride   = sizeof(TDME::uint16);

    auto sphereIB = engine.Device->CreateBuffer(ibDesc, sphereIndices.data());

    if (!sphereVB || !sphereIB)
    {
        MessageBoxA(nullptr, "Failed to create sphere buffers", "Error", MB_OK | MB_ICONERROR);
        return -1;
    }

    //////////////////////////////////////////////////////////////
    // Texture 로딩
    //////////////////////////////////////////////////////////////
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
    // 행성 생성
    //////////////////////////////////////////////////////////////

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
            engine.Context->SetPipelineState(psoStates[fillIndex][cullIndex].get());
        }
        if (engine.Input->IsKeyPressed(TDME::EKeys::F2))
        {
            cullIndex = (cullIndex + 1) % CULL_COUNT;
            engine.Context->SetPipelineState(psoStates[fillIndex][cullIndex].get());
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

        //////////////////////////////////////////////////////////////
        // 렌더링 시작 ----->
        //////////////////////////////////////////////////////////////
        engine.Renderer->BeginFrame(TDME::Colors::DARK_GRAY); // DEBUG: 회색 배경 테스트

        TDME::Matrix worldMatrix = TDME::ScaleMatrix(SPHERE_RADIUS, SPHERE_RADIUS, SPHERE_RADIUS);
        engine.Renderer->SetWorldMatrix(worldMatrix);

        // PSO + VB/IB 바인딩
        engine.Context->SetPipelineState(psoStates[fillIndex][cullIndex].get());
        engine.Context->SetVertexBuffer(0, sphereVB.get());
        engine.Context->SetIndexBuffer(sphereIB.get());

        engine.Context->DrawIndexed(indexCount);

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
