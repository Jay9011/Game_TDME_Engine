#pragma once

#include <Engine/RHI/State/IRasterizerState.h>
#include <Engine/RHI/State/Rasterizer/RasterizerStateDesc.h>

namespace TDME
{
    /**
     * @brief DX9 Rasterizer State 구현체
     * @details 바인딩 시 DX9Renderer가 Desc를 읽어 SetRenderState()로 적용. (DX9에는 네이티브 상태 객체가 없으므로 Desc만 저장)
     */
    class DX9RasterizerState : public IRasterizerState
    {
    public:
        explicit DX9RasterizerState(const RasterizerStateDesc& desc)
            : m_desc(desc)
        {
        }

        /**
         * @brief 상태 설정 구조체 반환
         * @return const RasterizerStateDesc& 상태 설정 구조체
         * @see TDME::RasterizerStateDesc
         */
        const RasterizerStateDesc& GetDesc() const override { return m_desc; }

    private:
        RasterizerStateDesc m_desc;
    };
} // namespace TDME