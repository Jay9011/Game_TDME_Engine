#pragma once

#include <Windows.h>

namespace TDME
{
    /**
     * @brief Win32 메시지 처리 인터페이스
     */
    class IWin32MessageProcessor
    {
    public:
        virtual ~IWin32MessageProcessor() = default;

        /**
         * @brief Win32 메시지 처리
         * @param hWnd 윈도우 핸들
         * @param message 메시지
         * @param wParam 추가 매개변수
         * @param lParam 추가 매개변수
         * @param outResult 처리 결과 (처리한 경우에만 유효)
         * @return true 처리 완료, false 처리 안 함
         */
        virtual bool ProcessMessage(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam, LRESULT& outResult) = 0;
    };
} // namespace TDME