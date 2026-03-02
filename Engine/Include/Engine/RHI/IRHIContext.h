#pragma once

#include <Core/CoreTypes.h>
#include <Core/Geometry/TRect.h>

#include "Engine/RHI/Shader/EShaderStage.h"

namespace TDME
{
    class IPipelineState;
    class IBuffer;
    class ITexture;
    struct Color;
    struct Viewport;

    /**
     * @brief RHI 컨텍스트 인터페이스
     * @details GPU 렌더링 명령(State 바인딩, 리소스 바인딩, 드로우 콜)을 수행하는 인터페이스.
     * @note DX11의 ID3D11DeviceContext에 대응하는 추상 인터페이스
     */
    class IRHIContext
    {
    public:
        virtual ~IRHIContext() = default;

        //////////////////////////////////////////////////////////////
        // PSO Binding
        //////////////////////////////////////////////////////////////

        /**
         * @brief 파이프라인 상태 객체 바인딩
         * @param pso 파이프라인 상태 객체 (VS, PS, InputLayout, RS, Blend, DS, Topology 통합)
         * @see TDME::IPipelineState
         */
        virtual void SetPipelineState(IPipelineState* pso) = 0;

        //////////////////////////////////////////////////////////////
        // IA (Input Assembler)
        //////////////////////////////////////////////////////////////

        /**
         * @brief 정점 버퍼 설정
         * @param buffer 정점 버퍼 객체
         * @see TDME::IBuffer
         */
        virtual void SetVertexBuffer(uint32 slot, IBuffer* buffer) = 0;

        /**
         * @brief 인덱스 버퍼 설정
         * @param buffer 인덱스 버퍼 객체
         * @see TDME::IBuffer
         */
        virtual void SetIndexBuffer(IBuffer* buffer) = 0;

        //////////////////////////////////////////////////////////////
        // RS (Rasterizer)
        //////////////////////////////////////////////////////////////

        /**
         * @brief 뷰포트 설정
         * @param viewport 뷰포트 설정
         * @see TDME::Viewport
         */
        virtual void SetViewport(const Viewport& viewport) = 0;

        /**
         * @brief 시저 렉트 설정
         * @param rect 시저 렉트 설정
         * @see TDME::RectI
         */
        virtual void SetScissorRect(const RectI& rect) = 0;

        //////////////////////////////////////////////////////////////
        // Resource Binding
        //////////////////////////////////////////////////////////////

        /**
         * @brief 상수 버퍼 바인딩
         * @param stage 바인딩할 셰이더 스테이지 (VS, PS)
         * @param slot 슬롯 번호 (0부터 시작)
         * @param buffer 상수 버퍼 객체
         * @note DX11: VSSetConstantBuffers / PSSetConstantBuffers로 분기
         */
        virtual void SetConstantBuffer(EShaderStage stage, uint32 slot, IBuffer* buffer) = 0;

        /**
         * @brief 텍스처 바인딩
         * @param stage 바인딩할 셰이더 스테이지 (VS, PS)
         * @param slot 슬롯 번호 (0부터 시작)
         * @param texture 텍스처 객체
         * @note DX11: VSSetShaderResources / PSSetShaderResources로 분기
         */
        virtual void SetTexture(EShaderStage stage, uint32 slot, ITexture* texture) = 0;

        //////////////////////////////////////////////////////////////
        // Update Buffer
        //////////////////////////////////////////////////////////////

        /**
         * @brief 동적 버퍼 매핑 (쓰기 접근)
         * @param buffer 매핑할 버퍼
         * @return void* CPU에서 쓸 수 있는 포인터
         * @note DX11: Map(WRITE_DISCARD), DX12: 내부 업로드 힙 할당
         */
        virtual void* MapBuffer(IBuffer* buffer) = 0;

        /**
         * @brief 동적 버퍼 언매핑
         * @param buffer 언매핑할 버퍼
         */
        virtual void UnmapBuffer(IBuffer* buffer) = 0;

        /**
         * @brief 버퍼 데이터 업데이트 (Map + memcpy + Unmap 헬퍼)
         * @param buffer 업데이트할 버퍼
         * @param data 소스 데이터 포인터
         * @param size 복사할 바이트 크기
         * @note DX11: UpdateSubresource 또는 Map+Unmap
         */
        virtual void UpdateBuffer(IBuffer* buffer, const void* data, uint32 size) = 0;

        //////////////////////////////////////////////////////////////
        // Draw Call
        //////////////////////////////////////////////////////////////

        /**
         * @brief 정점 버퍼 드로우
         * @param vertexCount 정점 개수
         * @param startVertex 시작 정점 인덱스
         */
        virtual void Draw(uint32 vertexCount, uint32 startVertex = 0) = 0;

        /**
         * @brief 인덱스 버퍼 드로우
         * @param indexCount 인덱스 개수
         * @param startIndex 시작 인덱스
         * @param baseVertex 기본 정점 인덱스
         */
        virtual void DrawIndexed(uint32 indexCount, uint32 startIndex = 0, int32 baseVertex = 0) = 0;

        //////////////////////////////////////////////////////////////
        // Clear
        //////////////////////////////////////////////////////////////

        /**
         * @brief 렌더 타겟(백버퍼) 클리어
         * @param color 클리어 색상
         * @see TDME::Color
         */
        virtual void ClearRenderTarget(const Color& color) = 0;

        /**
         * @brief 깊이/스텐실 버퍼 클리어
         * @param depth 깊이 클리어 값 (기본 1.0f = 가장 먼 거리)
         * @param stencil 스텐실 클리어 값 (기본 0 = 클리어 안함)
         */
        virtual void ClearDepthStencil(float depth = 1.0f, uint8 stencil = 0) = 0;
    };
} // namespace TDME