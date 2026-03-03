#pragma once

#include "ECullMode.h"
#include "EFillMode.h"

namespace TDME
{
    /**
     * @brief Rasterizer 상태 설정 구조체
     * @details Rasterizer 상태를 설정하는 구조체
     * @ref EFillMode "EFillMode"
     * @ref ECullMode "ECullMode"
     */
    struct RasterizerStateDesc
    {
        /** @brief 채우기 모드 */
        EFillMode FillMode = EFillMode::Solid;
        /** @brief 컬링 모드 */
        ECullMode CullMode = ECullMode::Back;
        /** @brief 반시계 방향 앞면 여부 */
        bool FrontCounterClockwise = false;
        /** @brief 깊이 클리핑 여부 */
        bool DepthClipEnable = true;
        /** @brief 사각형 클리핑 여부 */
        bool ScissorEnable = false;
    };
} // namespace TDME