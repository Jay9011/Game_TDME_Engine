#pragma once

#include "Engine/ApplicationCore/IApplication.h"
#include "Engine/ApplicationCore/WindowDesc.h"
#include "Engine/Input/IInputDevice.h"
#include "Engine/Time/ITimer.h"
#include "Engine/RHI/IRHIDevice.h"
#include "Engine/RHI/SwapChain/SwapChainDesc.h"
#include "Engine/Renderer/IRenderer.h"

#include <memory>

namespace TDME
{
    /**
     * @brief 엔진 팩토리 설정
     * @details 플랫폼 + 렌더러 생성에 필요한 설정을 묶은 구조체
     */
    struct EngineDesc
    {
        WindowDesc    Window;
        SwapChainDesc SwapChain;
    };

    /**
     * @brief 엔진 컨텍스트
     * @details Factory가 생성한 엔진 구성 요소들의 집합.
     * @note Application, Device, Renderer, Timer는 EngineContext가 소유
     * @note Window, Input 은 Application이 소유
     */
    struct EngineContext
    {
        std::unique_ptr<IApplication> Application;
        std::unique_ptr<IRHIDevice>   Device;
        std::unique_ptr<IRenderer>    Renderer;
        std::unique_ptr<ITimer>       Timer;

        IWindow*      Window = nullptr;
        IInputDevice* Input  = nullptr;

        /**
         * @brief 엔진 컨텍스트가 유효한지 확인
         * @details 모든 구성요소가 정상 생성되었는지 확인
         * @return true/false
         */
        [[nodiscard]] bool IsValid() const
        {
            return Application && Device && Renderer && Timer && Window && Input;
        }
    };

    /**
     * @brief 엔진 팩토리 함수 시그니처
     */
    using EngineFactoryFunc = EngineContext (*)(const EngineDesc&);
} // namespace TDME
