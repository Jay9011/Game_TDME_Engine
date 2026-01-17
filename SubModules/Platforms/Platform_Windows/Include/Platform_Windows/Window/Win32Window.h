#pragma once

#include "Platform_Windows/IWin32MessageProcessor.h"

#include <Engine/ApplicationCore/IWindow.h>
#include <Windows.h>

namespace TDME
{
    /**
     * @brief Win32 창 클래스
     */
    class Win32Window : public IWindow, public IWin32MessageProcessor
    {
    public:
        Win32Window();
        ~Win32Window() override;

        /**
         * @brief 창 생성
         * @param width 창의 너비
         * @param height 창의 높이
         * @param title 창의 제목
         * @return true / false
         */
        bool Create(int32 width, int32 height, const char* title) override;

        /**
         * @brief 런타임 중 창의 제목을 설정
         * @param title 창의 제목
         */
        void SetTitle(const char* title) override;

        //////////////////////////////////////////////////////////////
        // Win32 Window 관리
        //////////////////////////////////////////////////////////////

        /** @brief 네이티브 창 핸들 반환 */
        HWND GetHWnd() const { return m_hWnd; }

        /**
         * @brief Win32 메시지 처리
         * @param hWnd 윈도우 핸들
         * @param message 메시지
         * @param wParam 추가 매개변수
         * @param lParam 추가 매개변수
         * @param outResult 처리 결과 (처리한 경우에만 유효)
         * @return true 처리 완료, false 처리 안 함
         */
        bool ProcessMessage(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam, LRESULT& outResult) override;

        //////////////////////////////////////////////////////////////
        // Getter / Setter
        //////////////////////////////////////////////////////////////

        /**
         * @brief 창이 열려있는지 확인
         * @return true / false
         */
        bool IsOpen() const override;

        /**
         * @brief 창의 너비 반환
         * @return 창의 너비
         */
        int32 GetWidth() const override;

        /**
         * @brief 창의 높이 반환
         * @return 창의 높이
         */
        int32 GetHeight() const override;

        /**
         * @brief 네이티브 창 핸들 반환
         * @return 네이티브 창 핸들
         */
        void* GetNativeHandle() const override;

    private:
        /**
         * @brief 창 크기 변경 이벤트 처리
         *
         * @param width 창의 너비
         * @param height 창의 높이
         */
        void OnResize(int32 width, int32 height);

        /**
         * @brief 창 닫기 이벤트 처리
         */
        void OnClose();

        /**
         * @brief 문자열을 유니코드 문자열로 변환
         * @param str 변환할 문자열
         * @return wstring 유니코드 문자열
         */
        static wstring ToWideString(const string& str);

    private:
        HWND  m_hWnd   = nullptr;
        int32 m_width  = 0;
        int32 m_height = 0;
        bool  m_isOpen = false;
    };
} // namespace TDME
