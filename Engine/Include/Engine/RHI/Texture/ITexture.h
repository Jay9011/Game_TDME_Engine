#pragma once

#include <Core/CoreTypes.h>

#include "ETextureFormat.h"

namespace TDME
{
    /**
     * @brief 텍스처 인터페이스
     */
    class ITexture
    {
    public:
        virtual ~ITexture() = default;

        /**
         * @brief 텍스처의 너비
         * @return uint32 텍스처의 너비
         */
        virtual uint32 GetWidth() const = 0;
        /**
         * @brief 텍스처의 높이
         * @return uint32 텍스처의 높이
         */
        virtual uint32 GetHeight() const = 0;
        /**
         * @brief 텍스처의 밉맵 레벨 수
         * @return uint32 밉맵 레벨 수
         */
        virtual uint32 GetMipLevels() const = 0;
        /**
         * @brief 텍스처의 포맷
         * @return ETextureFormat 텍스처의 포맷
         */
        virtual ETextureFormat GetFormat() const = 0;
        /**
         * @brief 텍스처의 네이티브 핸들
         * @return void* 텍스처의 네이티브 핸들
         */
        virtual void* GetNativeHandle() const = 0;
    };
} // namespace TDME