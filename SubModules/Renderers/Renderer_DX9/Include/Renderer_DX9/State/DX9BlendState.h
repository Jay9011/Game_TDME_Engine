#pragma once

#include <Engine/RHI/State/IBlendState.h>

namespace TDME
{
    /**
     * @brief DX9 Blend State 구현체
     * @details 바인딩 시 DX9Renderer가 Desc를 읽어 SetRenderState()로 적용. (DX9에는 네이티브 상태 객체가 없으므로 Desc만 저장)
     */
    class DX9BlendState : public IBlendState
    {
    public:
        explicit DX9BlendState(const BlendStateDesc& desc)
            : m_desc(desc)
        {
        }

        /**
         * @brief 상태 설정 구조체 반환
         * @return const BlendStateDesc& 상태 설정 구조체
         * @see TDME::BlendStateDesc
         */
        const BlendStateDesc& GetDesc() const override { return m_desc; }

    private:
        BlendStateDesc m_desc;
    };
} // namespace TDME