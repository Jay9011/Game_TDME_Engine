#pragma once

#include <Core/CoreTypes.h>

namespace TDME
{
    class IWindow;
    class IApplicationMessageHandler;
    struct WindowDesc;

    /**
     * @brief 애플리케이션 인터페이스
     * @details OS 메시지 루프, 윈도우 생성, 이벤트 핸들러 관리 등
     * @ref "IWindow" TDME::IWindow
     * @ref "IApplicationMessageHandler" TDME::IApplicationMessageHandler
     * @ref "WindowDesc" TDME::WindowDesc
     */
    class IApplication
    {
    public:
        virtual ~IApplication() = default;

        //////////////////////////////////////////////////////////////
        // Message 처리
        //////////////////////////////////////////////////////////////

        /**
         * @brief 메시지 핸들러 설정
         * @param messageHandler 이벤트를 받을 핸들러 (nullptr로 해제)
         */
        virtual void SetMessageHandler(IApplicationMessageHandler* messageHandler) = 0;

        /**
         * @brief 대기중인 OS 메시지 처리
         * @details 매 프레임 호출하여 입력/윈도우 이벤트 등을 처리
         */
        virtual void ProcessMessages() = 0;

        //////////////////////////////////////////////////////////////
        // 윈도우 관리
        //////////////////////////////////////////////////////////////

        /**
         * @brief 윈도우 생성
         * @param windowDesc 윈도우 설정
         * @return 생성된 윈도우 객체 (실패시 nullptr)
         * @see TDME::WindowDesc
         */
        virtual IWindow* MakeWindow(const WindowDesc& windowDesc) = 0;

        /**
         * @brief 윈도우 제거
         * @param window 제거할 윈도우 객체
         */
        virtual void DestroyWindow(IWindow* window) = 0;

        //////////////////////////////////////////////////////////////
        // Application 관리
        //////////////////////////////////////////////////////////////

        /**
         * @brief 애플리케이션 종료 요청 여부 확인
         * @note Windows의 WM_QUIT 등...
         * @return true 종료 요청, false 종료 요청 아님
         */
        virtual bool IsQuitRequested() const = 0;

        /**
         * @brief 애플리케이션 종료 요청
         * @param exitCode 종료 코드
         */
        virtual void RequestQuit(int32 exitCode = 0) = 0;

        /**
         * @brief 종료 코드 반환
         * @return 종료 코드
         */
        virtual int32 GetExitCode() const = 0;
    };
} // namespace TDME