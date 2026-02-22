#pragma once

namespace TDME
{
    /**
     * @brief 렌더링 가능 인터페이스
     */
    class IRenderable
    {
    public:
        virtual ~IRenderable() = default;

        /**
         * @brief 매 프레임 렌더링 호출
         */
        virtual void Render() = 0;
    };
} // namespace TDME
