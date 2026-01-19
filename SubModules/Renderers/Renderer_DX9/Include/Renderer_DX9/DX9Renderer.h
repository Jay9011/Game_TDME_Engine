#pragma once

#include <Core/Math/TMatrix4x4.h>
#include <Engine/RHI/IRHIDevice.h>
#include <Engine/RHI/Vertex/IVertexLayout.h>
#include <Engine/Renderer/IRenderer.h>

#include "DX9VertexLayout.h"
#include <d3d9.h>
#include <Windows.h>
#include <memory>
#include <wrl/client.h>

namespace TDME
{
    using Microsoft::WRL::ComPtr; // ComPtr은 스마트 포인터와 비슷하게 사용하도록 별칭 선언 (namespace 충돌 염려 없을 것 같음)

    class DX9Renderer : public IRenderer
    {
    public:
        DX9Renderer();
        ~DX9Renderer() override;

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

        //////////////////////////////////////////////////////////////
        // 행렬 설정 (World, View, Projection)
        //////////////////////////////////////////////////////////////

        /**
         * @brief 월드 행렬 설정
         * @param matrix 월드 행렬
         * @see TDME::Matrix4x4
         */
        void SetWorldMatrix(const Matrix4& matrix) override;

        /**
         * @brief 뷰 행렬 설정
         * @param matrix 뷰 행렬
         * @see TDME::Matrix4x4
         */
        void SetViewMatrix(const Matrix4& matrix) override;

        /**
         * @brief 투영 행렬 설정
         * @param matrix 투영 행렬
         * @see TDME::Matrix4x4
         */
        void SetProjectionMatrix(const Matrix4& matrix) override;

        //////////////////////////////////////////////////////////////
        // 스프라이트 랜더링
        //////////////////////////////////////////////////////////////

        /**
         * @brief 스프라이트 랜더링
         * @param sprite 스프라이트 파라미터
         * @see TDME::SpriteDesc
         */
        void DrawSprite(const SpriteDesc& sprite) override;

        //////////////////////////////////////////////////////////////
        // 렌더링 설정
        //////////////////////////////////////////////////////////////

        /**
         * @brief 렌더링 설정 적용
         * @param settings 렌더링 설정
         * @see TDME::RenderSettings
         */
        void ApplyRenderSettings(const RenderSettings& settings) override;

        //////////////////////////////////////////////////////////////
        // 저수준 프리미티브 렌더링
        //////////////////////////////////////////////////////////////

        /**
         * @brief 정점 레이아웃 설정
         * @param layout 정점 레이아웃 (nullptr 면 해제)
         * @see TDME::IVertexLayout
         */
        void SetVertexLayout(IVertexLayout* layout) override;

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

        /**
         * @brief 삼각형 그리기
         * @param position 중심 위치 (화면 좌표계)
         * @param width 너비
         * @param height 높이
         * @param rotation 회전 각도 (도)
         * @param color 색상
         * @see TDME::Vector2
         * @see TDME::Color
         */
        void DrawTriangle(const Vector2& position, float width, float height, float rotation, const Color& color) override;

    private:
        /**
         * @brief Direct3D 인터페이스 (Factory) COM 객체
         * @note Direct3D9 API를 사용하기 위해 필요한 첫 번째 객체.
         * @li 어댑터 열거(Adapter Enumeration): 시스템에 설치된 그래픽 어댑터(GPU)가 몇 개인지, 각각의 이름과 드라이버 정보가 무엇인지 조회 가능.
         * @li 디스플레이 모드 열거: 지원하는 해상도, 주사율, 픽셀 포멧 조합을 조회.
         * @li 기능 검사(Capability Check): 특정 기능(멀티 샘플링, 특정 텍스처 포멧, 등)을 하드웨어가 지원하는지 확인.
         * @li 디바이스 생성: 위 정보를 바탕으로 결정한 설정으로 실제 렌더링 디바이스 생성.
         *
         * @see Direct3D9::GetAdapterCount()
         * @see Direct3D9::GetAdapterIdentifier()
         * @see Direct3D9::GetAdapterDisplayMode()
         * @see Direct3D9::CheckDeviceType()
         * @see Direct3D9::CheckDeviceFormat()
         * @see Direct3D9::CheckDeviceFormatConversion()
         * @see Direct3D9::CheckDeviceMultiSampleType()
         * @see Direct3D9::CheckDeviceFormatConversion()
         * @see Direct3D9::CheckDeviceFormatConversion()
         */
        ComPtr<IDirect3D9> m_d3d;

        /**
         * @brief 렌더링 디바이스 (리소스 생성 + 렌더링) COM 객체
         * @note 실제 렌더링을 담당하는 IDirect3DDevice9 인터페이스를 구현한 COM 객체.
         * @li 리소스 생성 (텍스처, 버텍스 버퍼, 인덱스 버퍼, 셰이더)
         * @li 렌더링 상태 설정 (블렌딩, 깊이 테스트, 컬링, 등)
         * @li 드로우 콜 실행 (DrawPrimitive, DrawIndexedPrimitive, DrawTriangles, 등)
         * @li 화면 표시 (Present)
         *
         * @see Direct3DDevice9::CreateTexture()
         * @see Direct3DDevice9::CreateVertexBuffer()
         * @see Direct3DDevice9::CreateIndexBuffer()
         * @see Direct3DDevice9::CreateShader()
         * @see Direct3DDevice9::SetRenderState()
         * @see Direct3DDevice9::DrawPrimitive()
         * @see Direct3DDevice9::DrawIndexedPrimitive()
         * @see Direct3DDevice9::DrawTriangles()
         * @see Direct3DDevice9::Present()
         */
        ComPtr<IDirect3DDevice9> m_device;

        IVertexLayout*                   m_currentLayout = nullptr;
        std::unique_ptr<DX9VertexLayout> m_layoutPC;

        static constexpr DWORD FVF_VERTEX2D = D3DFVF_XYZRHW | D3DFVF_DIFFUSE;
    };
} // namespace TDME