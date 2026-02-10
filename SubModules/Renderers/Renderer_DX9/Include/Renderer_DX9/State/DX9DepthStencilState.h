#pragma once

#include <Engine/RHI/State/DepthStencil/DepthStencilStateDesc.h>
#include <Engine/RHI/State/IDepthStencilState.h>

namespace TDME
{
    /**
     * @brief DX9 깊이/스텐실 상태 구현체
     * @details 바인딩 시 DX9Renderer가 Desc를 읽어 SetRenderState()로 적용. (DX9에는 네이티브 상태 객체가 없으므로 Desc만 저장)
     */
    class DX9DepthStencilState : public IDepthStencilState
    {
    public:
        explicit DX9DepthStencilState(const DepthStencilStateDesc& desc)
            : m_desc(desc)
        {
        }

        /**
         * @brief 상태 설정 구조체 반환
         * @return const DepthStencilStateDesc& 상태 설정 구조체
         * @see TDME::DepthStencilStateDesc
         */
        const DepthStencilStateDesc& GetDesc() const override { return m_desc; }

    private:
        DepthStencilStateDesc m_desc;
    };
} // namespace TDME