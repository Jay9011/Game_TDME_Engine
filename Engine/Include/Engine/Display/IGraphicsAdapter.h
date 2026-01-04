#pragma once

#include "DisplayMode.h"
#include "GraphicsAdapterDesc.h"
#include <vector>

namespace TDME
{
    /**
     * @brief 그래픽 어댑터(GPU) 인터페이스
     * @details GPU 정보 조회 및 디스플레이 모드 관리 기능 제공
     * @ref GraphicsAdapterDesc "GraphicsAdapterDesc"
     */
    class IGraphicsAdapter
    {
    public:
        virtual ~IGraphicsAdapter() = default;

        /**
         * @brief 그래픽 어댑터(GPU) 정보를 반환합니다.
         * @ref GraphicsAdapterDesc "GraphicsAdapterDesc"
         * @return 그래픽 어댑터(GPU) 정보
         */
        virtual const GraphicsAdapterDesc& GetDesc() const = 0;

        /**
         * @brief 지원하는 디스플레이 모드 목록을 반환합니다.
         * @ref DisplayMode "DisplayMode"
         * @return 디스플레이 모드 목록
         */
        virtual std::vector<DisplayMode> EnumerateDisplayModes() const = 0;

        /**
         * @brief 현재 디스플레이 모드를 반환합니다.
         * @ref DisplayMode "DisplayMode"
         * @return 현재 디스플레이 모드
         */
        virtual DisplayMode GetCurrentDisplayMode() const = 0;

        /**
         * @brief 특정 디스플레이 모드가 지원되는지 확인합니다.
         * @param mode 디스플레이 모드
         * @return 지원 여부
         */
        virtual bool IsDisplayModeSupported(const DisplayMode& mode) const = 0;
    };
} // namespace TDME