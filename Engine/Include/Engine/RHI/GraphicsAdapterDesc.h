#pragma once

#include <Core/CoreTypes.h>
#include <cstddef>

#include "EGPUVendor.h"

namespace TDME
{
    /**
     * @brief 그래픽 어댑터(GPU) 정보의 구조체
     * @ref EGPUVendor "EGPUVendor"
     */
    struct GraphicsAdapterDesc
    {
        uint32     Index;                 // 어댑터 인덱스 (0부터)
        string     Description;           // GPU 이름 (예: "NVIDIA GeForce RTX 3070", "AMD Radeon RX 6800 XT")
        EGPUVendor Vendor;                // GPU 제조사
        uint32     VendorID;              // PCI 벤더 ID
        uint32     DeviceID;              // PCI 디바이스 ID
        size_t     DedicatedVideoMemory;  // 전용 비디오 메모리(VRAM) 크기 (바이트)
        size_t     DedicatedSystemMemory; // 전용 시스템 메모리 크기 (바이트)
        size_t     SharedSystemMemory;    // 공유 시스템 메모리 크기 (바이트)

        FORCE_INLINE constexpr uint32 GetVideoMemoryMB() const
        {
            return static_cast<uint32>(DedicatedVideoMemory / (1024 * 1024));
        }
    };
} // namespace TDME