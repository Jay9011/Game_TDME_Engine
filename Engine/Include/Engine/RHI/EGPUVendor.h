#pragma once

#include "Core/CoreMacros.h"
#include <Core/CoreTypes.h>

namespace TDME
{
    /**
     * @brief GPU 제조사 열거형
     */
    enum class EGPUVendor : uint8
    {
        Unknown,   // 알 수 없음
        NVIDIA,    // NVIDIA
        AMD,       // AMD
        Intel,     // Intel
        Microsoft, // Microsoft
    };

    /**
     * @brief 제조사 ID(PCI 벤더 ID)를 기반으로 GPU 제조사를 반환
     * @param vendorID 제조사 ID
     * @see https://admin.pci-ids.ucw.cz/read/PC?restrict= "PCI 벤더 ID 목록"
     * @ref EGPUVendor "EGPUVendor"
     * @return 제조사 ID에 해당하는 EGPUVendor
     */
    FORCE_INLINE EGPUVendor GetGPUVendorFromID(uint32 vendorID)
    {
        switch (vendorID)
        {
        case 0x10DE: return EGPUVendor::NVIDIA;    // NVIDIA Corporation
        case 0x1002: return EGPUVendor::AMD;       // Advanced Micro Devices, Inc. [AMD/ATI]
        case 0x8086: return EGPUVendor::Intel;     // Intel Corporation
        case 0x1414: return EGPUVendor::Microsoft; // Microsoft Corporation
        default:     return EGPUVendor::Unknown;
        }
    }

    /**
     * @brief EGPUVendor를 문자열로 반환
     * @param vendor EGPUVendor
     * @return 제조사 이름
     */
    FORCE_INLINE const char* GetGPUVendorName(EGPUVendor vendor)
    {
        switch (vendor)
        {
        case EGPUVendor::NVIDIA:    return "NVIDIA";
        case EGPUVendor::AMD:       return "AMD";
        case EGPUVendor::Intel:     return "Intel";
        case EGPUVendor::Microsoft: return "Microsoft";
        default:                    return "Unknown";
        }
    }
} // namespace TDME