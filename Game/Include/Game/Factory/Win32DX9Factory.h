#pragma once

#include <Engine/EngineContext.h>

namespace TDME
{
    /**
     * @brief Win32 + DX9 엔진 생성
     * @details Win32Application, DX9Device, DX9Renderer, Win32Timer를 조합해서 EngineContext를 생성하는 Concrete Factory 함수
     * @param desc 엔진 팩토리 설정
     * @return EngineContext 생성된 엔진 컨텍스트 (IsValid()가 true여야 함)
     */
    EngineContext CreateWin32DX9Engine(const EngineDesc& desc);
} // namespace TDME