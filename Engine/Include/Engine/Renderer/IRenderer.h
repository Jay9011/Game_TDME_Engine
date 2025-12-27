#pragma once

namespace TDME
{
    class IWindow;
    struct Color;

    class IRenderer
    {
    public:
        virtual ~IRenderer() = default;

        /**
         * @brief 렌더러를 초기화합니다.
         * @param window 창 객체
         * @return true 성공, false 실패
         * @see TDME::IWindow
         */
        virtual bool Initialize(IWindow* window) = 0;

        /**
         * @brief 렌더러를 종료합니다.
         */
        virtual void Shutdown() = 0;

        /**
         * @brief 프레임을 시작합니다.
         * @note 백버퍼를 클리어하고 프레임을 시작.
         * @param clearColor 클리어 색상
         * @see TDME::Color
         */
        virtual void BeginFrame(const Color& clearColor) = 0;

        /**
         * @brief 프레임을 종료합니다.
         * @note 백버퍼를 화면에 출력.
         */
        virtual void EndFrame() = 0;
    };
} // namespace TDME