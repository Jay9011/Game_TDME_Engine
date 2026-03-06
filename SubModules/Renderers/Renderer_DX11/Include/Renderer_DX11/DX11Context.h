#pragma once

#include <Engine/RHI/IRHIContext.h>

#include <d3d11.h>

namespace TDME
{
    class DX11Device;

    /**
     * @brief DX11 Context 클래스
     * @details ID3D11DeviceContext 래핑. SetPipelineState를 개별 DX11 호출로 분해
     */
    class DX11Context : public IRHIContext
    {
    public:
        DX11Context(DX11Device* device, ID3D11DeviceContext* nativeContext);
        ~DX11Context() override = default;

        //////////////////////////////////////////////////////////////
        // PSO Binding
        //////////////////////////////////////////////////////////////

        /**
         * @brief 파이프라인 상태 객체 바인딩
         * @param pso 파이프라인 상태 객체 (VS, PS, InputLayout, RS, Blend, DS, Topology 통합)
         * @see TDME::IPipelineState
         */
        void SetPipelineState(IPipelineState* pso) override;

        //////////////////////////////////////////////////////////////
        // IA (Input Assembler)
        //////////////////////////////////////////////////////////////

        /**
         * @brief 정점 버퍼 설정
         * @param buffer 정점 버퍼 객체
         * @see TDME::IBuffer
         */
        void SetVertexBuffer(uint32 slot, IBuffer* buffer) override;

        /**
         * @brief 인덱스 버퍼 설정
         * @param buffer 인덱스 버퍼 객체
         * @see TDME::IBuffer
         */
        void SetIndexBuffer(IBuffer* buffer) override;

        //////////////////////////////////////////////////////////////
        // RS (Rasterizer)
        //////////////////////////////////////////////////////////////

        /**
         * @brief 뷰포트 설정
         * @param viewport 뷰포트 설정
         * @see TDME::Viewport
         */
        void SetViewport(const Viewport& viewport) override;

        /**
         * @brief 시저 렉트 설정
         * @param rect 시저 렉트 설정
         * @see TDME::RectI
         */
        void SetScissorRect(const RectI& rect) override;

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
        void SetConstantBuffer(EShaderStage stage, uint32 slot, IBuffer* buffer) override;

        /**
         * @brief 텍스처 바인딩
         * @param stage 바인딩할 셰이더 스테이지 (VS, PS)
         * @param slot 슬롯 번호 (0부터 시작)
         * @param texture 텍스처 객체
         * @note DX11: VSSetShaderResources / PSSetShaderResources로 분기
         */
        void SetTexture(EShaderStage stage, uint32 slot, ITexture* texture) override;

        //////////////////////////////////////////////////////////////
        // Update Buffer
        //////////////////////////////////////////////////////////////

        /**
         * @brief 동적 버퍼 매핑 (쓰기 접근)
         * @param buffer 매핑할 버퍼
         * @return void* CPU에서 쓸 수 있는 포인터
         * @note DX11: Map(WRITE_DISCARD), DX12: 내부 업로드 힙 할당
         */
        void* MapBuffer(IBuffer* buffer) override;

        /**
         * @brief 동적 버퍼 언매핑
         * @param buffer 언매핑할 버퍼
         */
        void UnmapBuffer(IBuffer* buffer) override;

        /**
         * @brief 버퍼 데이터 업데이트 (Map + memcpy + Unmap 헬퍼)
         * @param buffer 업데이트할 버퍼
         * @param data 소스 데이터 포인터
         * @param size 복사할 바이트 크기
         * @note DX11: UpdateSubresource 또는 Map+Unmap
         */
        void UpdateBuffer(IBuffer* buffer, const void* data, uint32 size) override;

        //////////////////////////////////////////////////////////////
        // Draw Call
        //////////////////////////////////////////////////////////////

        /**
         * @brief 정점 버퍼 드로우
         * @param vertexCount 정점 개수
         * @param startVertex 시작 정점 인덱스
         */
        void Draw(uint32 vertexCount, uint32 startVertex = 0) override;

        /**
         * @brief 인덱스 버퍼 드로우
         * @param indexCount 인덱스 개수
         * @param startIndex 시작 인덱스
         * @param baseVertex 기본 정점 인덱스
         */
        void DrawIndexed(uint32 indexCount, uint32 startIndex = 0, int32 baseVertex = 0) override;

        //////////////////////////////////////////////////////////////
        // Clear
        //////////////////////////////////////////////////////////////

        /**
         * @brief 렌더 타겟(백버퍼) 클리어
         * @param color 클리어 색상
         * @see TDME::Color
         */
        void ClearRenderTarget(const Color& color) override;

        /**
         * @brief 깊이/스텐실 버퍼 클리어
         * @param depth 깊이 클리어 값 (기본 1.0f = 가장 먼 거리)
         * @param stencil 스텐실 클리어 값 (기본 0 = 클리어 안함)
         */
        void ClearDepthStencil(float depth = 1.0f, uint8 stencil = 0) override;

    private:
        DX11Device*          m_device  = nullptr;
        ID3D11DeviceContext* m_context = nullptr;
    };
} // namespace TDME