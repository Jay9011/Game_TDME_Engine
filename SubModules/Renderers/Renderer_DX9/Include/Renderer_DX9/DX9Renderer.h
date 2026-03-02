#pragma once

#include <Core/Math/TMatrix4x4.h>
#include <Engine/RHI/IRHIContext.h>
#include <Engine/RHI/IRHIDevice.h>
#include <Engine/Renderer/EPrimitiveType.h>
#include <Engine/Renderer/IRenderer.h>

#include <d3d9.h>
#include <memory>

namespace TDME
{
    class DX9Device;
    class IInputLayout;

    /**
     * @brief DX9 Renderer (IRenderer + IRHIContext)
     * @note DX9에서는 IDirect3DDevice9 하나가 모든 역할을 하므로 단일 클래스로 구현.
     */
    class DX9Renderer : public IRenderer, public IRHIContext
    {
    public:
        DX9Renderer();
        ~DX9Renderer() override;

        //////////////////////////////////////////////////////////////
        // IRenderer
        //////////////////////////////////////////////////////////////

        /**
         * @brief 렌더러를 초기화합니다.
         * @param window 창 객체
         * @return true 성공, false 실패
         * @see TDME::IWindow
         */
        bool Initialize(IWindow* window) override;

        /**
         * @brief 렌더러를 종료합니다.
         */
        void Shutdown() override;

        /**
         * @brief 프레임을 시작합니다.
         */
        void BeginFrame(const Color& clearColor) override;

        /**
         * @brief 프레임을 종료합니다.
         */
        void EndFrame() override;

        /**
         * @brief 월드 행렬 설정
         * @param matrix 월드 행렬
         * @see TDME::Matrix
         */
        void SetWorldMatrix(const Matrix& matrix) override;

        /**
         * @brief 뷰 행렬 설정
         * @param matrix 뷰 행렬
         * @see TDME::Matrix
         */
        void SetViewMatrix(const Matrix& matrix) override;

        /**
         * @brief 투영 행렬 설정
         * @param matrix 투영 행렬
         * @see TDME::Matrix
         */
        void SetProjectionMatrix(const Matrix& matrix) override;

        /**
         * @brief 렌더링 설정 적용
         * @param settings 렌더링 설정
         * @see TDME::RenderSettings
         */
        void ApplyRenderSettings(const RenderSettings& settings) override;

        /**
         * @brief 스프라이트 랜더링
         * @param sprite 스프라이트 파라미터
         * @see TDME::SpriteDesc
         */
        void DrawSprite(const SpriteDesc& sprite) override;

        /**
         * @brief 프리미티브 타입 렌더링 (점, 선, 면)
         * @param type 프리미티브 타입
         * @param vertices 정점 데이터 포인터
         * @param vertexCount 정점 개수
         * @param stride 정점 하나의 바이트 크기
         * @see TDME::EPrimitiveType
         * @see TDME::void*
         * @see TDME::uint32
         */
        void DrawPrimitives(EPrimitiveType type, const void* vertices, uint32 vertexCount, uint32 stride) override;

        //////////////////////////////////////////////////////////////
        // IRHIContext
        //////////////////////////////////////////////////////////////

        /**
         * @brief 파이프라인 상태 객체 바인딩
         * @param pso 파이프라인 상태 객체 (VS, PS, InputLayout, RS, Blend, DS, Topology 통합)
         * @see TDME::IPipelineState
         */
        void SetPipelineState(IPipelineState* pso) override;

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

        //////////////////////////////////////////////////////////////
        // Getter / Setter
        //////////////////////////////////////////////////////////////

        /**
         * @brief 디바이스 설정
         * @param device 디바이스
         * @see TDME::DX9Device
         */
        void SetDevice(DX9Device* device);

    private:
        DX9Device*        m_device          = nullptr;                      // Engine 디바이스 객체
        IDirect3DDevice9* m_nativeDevice    = nullptr;                      // Direct3D 9 디바이스 객체
        IInputLayout*     m_currentLayout   = nullptr;                      // 현재 사용 중인 정점 레이아웃
        EPrimitiveType    m_currentTopology = EPrimitiveType::TriangleList; // 현재 사용 중인 프리미티브 타입
    };
} // namespace TDME