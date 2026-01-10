#include "pch.h"

#include <Core/Types/Color.h>
#include <Core/Math/TVector2.h>
#include <Engine/ApplicationCore/Input/Windows/EKeyCode.h>
#include <Platform_Windows/Win32Window.h>
#include <Platform_Windows/Time/Win32Timer.h>
#include <Platform_Windows/Input/Win32Input.h>
#include <Renderer_DX9/DX9Renderer.h>

#include "Game/Types/Color.h"

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine,
                   _In_ int nCmdShow)
{
    UNREFERENCED_PARAMETER(hInstance);
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);
    UNREFERENCED_PARAMETER(nCmdShow);

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

    // 3. Timer 와 Input 생성
    TDME::Win32Timer timer;
    TDME::Win32Input input;
    timer.Reset();
    input.Initialize(&window);

    // DEBUG: 삼각형 테스트
    float       rotation      = 0.0f;
    float       width         = 100.0f;
    float       height        = 100.0f;
    TDME::Color triangleColor = TDME::Colors::WHITE;

    constexpr float ROTATION_SPEED = 180.0f; // 1초에 180도 회전
    constexpr float SIZE_SPEED     = 100.0f; // 1초에 100픽셀 이동

    // Main loop
    while (window.IsOpen())
    {
        //////////////////////////////////////////////////////////////
        // 시간 관련 로직
        //////////////////////////////////////////////////////////////
        timer.Tick();
        float deltaTime = timer.GetDeltaTime();
        //////////////////////////////////////////////////////////////
        // 입력 및 이벤트 처리
        //////////////////////////////////////////////////////////////
        input.Update();
        window.PollEvents();
        //////////////////////////////////////////////////////////////
        // 게임 Update 로직
        //////////////////////////////////////////////////////////////
        // TODO: Update 게임 로직
        // DEBUG: 입력 테스트
        // 색상 변경
        if (input.IsKeyPressed(TDME::EKeyCode::W))
            triangleColor = TDME::Colors::WHITE;
        if (input.IsKeyPressed(TDME::EKeyCode::A))
            triangleColor = TDME::Colors::AQUA;
        if (input.IsKeyPressed(TDME::EKeyCode::S))
            triangleColor = TDME::Colors::SAGE_GREEN;
        if (input.IsKeyPressed(TDME::EKeyCode::D))
            triangleColor = TDME::Colors::DARK_VIOLET;
        // 회전 (Space를 누르고 있는 동안)
        if (input.IsKeyDown(TDME::EKeyCode::Space))
            rotation += ROTATION_SPEED * deltaTime;
        // 크기 조절 (화살표를 누르고 있는 동안)
        if (input.IsKeyDown(TDME::EKeyCode::Up))
            height += SIZE_SPEED * deltaTime;
        if (input.IsKeyDown(TDME::EKeyCode::Down))
            height -= SIZE_SPEED * deltaTime;
        if (input.IsKeyDown(TDME::EKeyCode::Left))
            width -= SIZE_SPEED * deltaTime;
        if (input.IsKeyDown(TDME::EKeyCode::Right))
            width += SIZE_SPEED * deltaTime;
        // 크기 최소값 제한
        width  = std::max<float>(width, 10.0f);
        height = std::max<float>(height, 10.0f);
        // 마우스 위치
        TDME::Vector2 mousePosition = input.GetMousePosition();

        //////////////////////////////////////////////////////////////
        // 렌더링 시작 ----->
        //////////////////////////////////////////////////////////////
        // DEBUG: 회색 배경 테스트
        renderer.BeginFrame(TDME::Colors::DARK_GRAY);

        // TODO: Render 렌더링
        // DEBUG: 삼각형 그리기
        renderer.DrawTriangle(mousePosition, width, height, rotation, triangleColor);

        renderer.EndFrame();
        //////////////////////////////////////////////////////////////
        // <----- 렌더링 종료
        //////////////////////////////////////////////////////////////
    }

    renderer.Shutdown();
    return 0;
}
