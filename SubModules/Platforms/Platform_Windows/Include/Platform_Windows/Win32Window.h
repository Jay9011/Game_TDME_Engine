#pragma once

#include <Engine/Platform/IWindow.h>
#include <Windows.h>

namespace TDME
{
    /**
     * @brief Win32 창 클래스
     */
    class Win32Window : public IWindow
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
         * @brief 이벤트 처리
         */
        void PollEvents() override;

        /**
         * @brief 런타임 중 창의 제목을 설정
         * @param title 창의 제목
         */
        void SetTitle(const char* title) override;

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
        /** @brief 윈도우 클래스 이름 */
        static constexpr const WCHAR* WINDOW_CLASS_NAME = L"TDME_WindowClass";

        /** @brief 윈도우 클래스 등록 여부 */
        static bool s_classRegistered;

        HWND  m_hWnd;
        int32 m_width;
        int32 m_height;
        bool  m_isOpen;

        /**
         * @brief 윈도우 클래스 등록
         * @param hInstance 인스턴스 핸들
         * @return ATOM 윈도우 클래스 식별 번호(?)
         */
        static ATOM MyRegisterClass(HINSTANCE hInstance);

        /**
         * @brief 윈도우 프로시저 (명령 처리)
         * @param hWnd 창 핸들
         * @param message 메시지
         * @param wParam 추가 매개변수
         * @param lParam 추가 매개변수
         * @return LRESULT 처리 결과
         */
        static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

        /**
         * @brief 문자열을 유니코드 문자열로 변환
         * @param str 변환할 문자열
         * @return wstring 유니코드 문자열
         */
        static wstring ToWideString(const string& str);
    };
} // namespace TDME
