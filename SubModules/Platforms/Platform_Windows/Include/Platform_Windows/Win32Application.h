#pragma once

#include <Engine/ApplicationCore/IApplication.h>

#include <Windows.h>
#include <memory>
#include <vector>

namespace TDME
{
    class Win32Window;
    class Win32Input;
    struct WindowDesc;

    /**
     * @brief Win32 애플리케이션 클래스
     * @details OS 메시지 루프, 윈도우 관리, 입력 처리 등
     * @ref "IApplication" TDME::IApplication
     * @ref "Win32Window" TDME::Win32Window
     * @ref "Win32Input" TDME::Win32Input
     * @ref "WindowDesc" TDME::WindowDesc
     */
    class Win32Application : public IApplication
    {
    public:
        Win32Application();
        ~Win32Application();

        //////////////////////////////////////////////////////////////
        // Message 처리
        //////////////////////////////////////////////////////////////

        /**
         * @brief 메시지 핸들러 설정
         * @param messageHandler 이벤트를 받을 핸들러 (nullptr로 해제)
         */
        void SetMessageHandler(IApplicationMessageHandler* messageHandler) override;

        /**
         * @brief 대기중인 OS 메시지 처리 (메시지 루프)
         * @details 매 프레임 호출하여 입력/윈도우 이벤트 등을 처리
         */
        void ProcessMessages() override;

        //////////////////////////////////////////////////////////////
        // 윈도우 관리
        //////////////////////////////////////////////////////////////

        /**
         * @brief 윈도우 생성
         * @param windowDesc 윈도우 설정
         * @return 생성된 윈도우 객체 (실패시 nullptr)
         * @see TDME::WindowDesc
         */
        IWindow* MakeWindow(const WindowDesc& windowDesc) override;

        /**
         * @brief 윈도우 제거
         * @param window 제거할 윈도우 객체
         */
        void DestroyWindow(IWindow* window) override;

        //////////////////////////////////////////////////////////////
        // Application 관리
        //////////////////////////////////////////////////////////////
        /**
         * @brief 애플리케이션 종료 요청 여부 확인
         * @note Windows의 WM_QUIT 등...
         * @return true 종료 요청, false 종료 요청 아님
         */
        bool IsQuitRequested() const override;

        /**
         * @brief 애플리케이션 종료 요청
         * @param exitCode 종료 코드
         */
        void RequestQuit(int32 exitCode = 0) override;

        /**
         * @brief 종료 코드 반환
         * @return 종료 코드
         */
        int32 GetExitCode() const override;

        //////////////////////////////////////////////////////////////
        // Win32 Application 관리
        //////////////////////////////////////////////////////////////
        /**
         * @brief Win32 메시지 처리
         * @param hWnd 윈도우 핸들
         * @param message 메시지
         * @param wParam 추가 매개변수
         * @param lParam 추가 매개변수
         */
        static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

        //////////////////////////////////////////////////////////////
        // Getter / Setter
        //////////////////////////////////////////////////////////////
        /**
         * @brief 인스턴스 반환
         * @return TDME::Win32Application* 인스턴스
         */
        static Win32Application* GetInstance() { return s_instance; }

        /**
         * @brief 입력 장치
         * @return TDME::Win32Input* 입력장치
         */
        Win32Input* GetInput() const { return m_input.get(); }

        /**
         * @brief 메시지 핸들러
         * @return TDME::IApplicationMessageHandler* 메시지 핸들러
         */
        IApplicationMessageHandler* GetMessageHandler() const { return m_messageHandler; }

    private:
        /**
         * @brief 윈도우 클래스 등록
         * @return true 성공, false 실패
         */
        bool RegisterWindowClass();

        /**
         * @brief HWND를 통해 윈도우 찾기
         * @param hWnd 윈도우 핸들
         * @return Win32Window* 윈도우 객체 (찾지 못하면 nullptr)
         */
        Win32Window* FindWindowByHandle(HWND hWnd) const;

    private:
        static Win32Application* s_instance;
        static bool              s_classRegistered;

        std::vector<std::unique_ptr<Win32Window>> m_windows;
        std::unique_ptr<Win32Input>               m_input;
        IApplicationMessageHandler*               m_messageHandler = nullptr;

        bool  m_quitRequested = false;
        int32 m_exitCode      = 0;
    };
} // namespace TDME