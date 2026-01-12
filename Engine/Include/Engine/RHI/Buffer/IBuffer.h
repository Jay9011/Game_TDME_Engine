#pragma once

#include "EBufferType.h"
#include "EBufferUsage.h"

namespace TDME
{
    /**
     * @brief 버퍼 인터페이스
     * @details 버퍼의 타입, 사용 목적, 크기 등을 제공하는 인터페이스
     * @ref EBufferType "EBufferType"
     * @ref EBufferUsage "EBufferUsage"
     */
    class IBuffer
    {
    public:
        virtual ~IBuffer() = default;

        /**
         * @brief 버퍼 데이터 갱신 (Dynamic 버퍼용)
         * @param data 데이터 포인터
         * @param size 데이터 크기 (바이트)
         * @return true/false 성공/실패
         */
        virtual bool Update(const void* data, uint32 size) = 0;

        //////////////////////////////////////////////////////////////
        // Getter
        //////////////////////////////////////////////////////////////

        virtual EBufferType  GetType() const         = 0;
        virtual EBufferUsage GetUsage() const        = 0;
        virtual uint32       GetByteSize() const     = 0;
        virtual uint32       GetStride() const       = 0;
        virtual void*        GetNativeHandle() const = 0;
    };
} // namespace TDME