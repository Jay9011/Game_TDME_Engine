#pragma once

#include "Core/CoreTypes.h"

namespace TDME
{
    class IWindow
    {
    public:
        virtual ~IWindow() = default;

        /**
         * @brief 창을 생성합니다.
         *
         * @param width 창의 너비
         * @param height 창의 높이
         * @param title 창의 제목
         * @return 성공 여부
         */
        virtual bool Create(int32 width, int32 height, const char *title) = 0;

        /**
         * @brief 창이 열려있는지 확인합니다.
         * @return 창이 열려있는지 여부
         */
        virtual bool IsOpen() const = 0;

        /**
         * @brief 창의 너비를 반환합니다.
         * @return 창의 너비
         */
        virtual int32 GetWidth() const = 0;

        /**
         * @brief 창의 높이를 반환합니다.
         * @return 창의 높이
         */
        virtual int32 GetHeight() const = 0;

        /**
         * @brief 매 프레임마다 이벤트를 처리합니다.
         */
        virtual void PollEvents() = 0;

        /**
         * @brief 플랫폼 네이티브 창 핸들을 반환합니다.
         * @note Window의 경우 HWND, Mac의 경우 NSWindow* 등을 반환하기 위한 용도입니다.
         *
         * @return void* 형태의 네이티브 창 핸들
         */
        virtual void *GetNativeHandle() const = 0;
    };
} // namespace TDME