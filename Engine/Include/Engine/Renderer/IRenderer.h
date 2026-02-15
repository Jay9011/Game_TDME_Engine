#pragma once

#include <Core/Math/TMatrix4x4.h>
#include <Core/Math/TVector2.h>

#include "EPrimitiveType.h"

namespace TDME
{
    class IWindow;
    class ITexture;
    class IVertexLayout;
    class IRasterizerState;
    class IBlendState;
    class IDepthStencilState;
    struct SpriteDesc;
    struct RenderSettings;
    struct Color;

    /**
     * @brief 렌더러 인터페이스
     * @note 렌더러 기능을 제공하는 인터페이스
     */
    class IRenderer
    {
    public:
        virtual ~IRenderer() = default;

        /**
         * @brief 렌더러를 초기화합니다.
         * @param window 창 객체
         * @return true 성공, false 실패
         * @see TDME::IWindow
         */
        virtual bool Initialize(IWindow* window) = 0;

        /**
         * @brief 렌더러를 종료합니다.
         */
        virtual void Shutdown() = 0;

        /**
         * @brief 프레임을 시작합니다.
         * @note 백버퍼를 클리어하고 프레임을 시작.
         * @param clearColor 클리어 색상
         * @see TDME::Color
         */
        virtual void BeginFrame(const Color& clearColor) = 0;

        /**
         * @brief 프레임을 종료합니다.
         * @note 백버퍼를 화면에 출력.
         */
        virtual void EndFrame() = 0;

        //////////////////////////////////////////////////////////////
        // 행렬 설정 (World, View, Projection)
        //////////////////////////////////////////////////////////////

        /**
         * @brief 월드 행렬 설정
         * @param matrix 월드 행렬
         * @see TDME::Matrix
         */
        virtual void SetWorldMatrix(const Matrix& matrix) = 0;

        /**
         * @brief 뷰 행렬 설정
         * @param matrix 뷰 행렬
         * @see TDME::Matrix
         */
        virtual void SetViewMatrix(const Matrix& matrix) = 0;

        /**
         * @brief 투영 행렬 설정
         * @param matrix 투영 행렬
         * @see TDME::Matrix
         */
        virtual void SetProjectionMatrix(const Matrix& matrix) = 0;

        //////////////////////////////////////////////////////////////
        // 상태 객체 바인딩
        //////////////////////////////////////////////////////////////

        /**
         * @brief 래스터라이저 상태 바인딩
         * @param state 래스터라이저 상태 객체 (nullptr이면 무시)
         * @see TDME::IRasterizerState
         */
        virtual void SetRasterizerState(IRasterizerState* state) = 0;

        /**
         * @brief 블렌딩 상태 바인딩
         * @param state 블렌딩 상태 객체 (nullptr이면 무시)
         * @see TDME::IBlendState
         */
        virtual void SetBlendState(IBlendState* state) = 0;

        /**
         * @brief 깊이/스텐실 상태 바인딩
         * @param state 깊이/스텐실 상태 객체 (nullptr이면 무시)
         * @see TDME::IDepthStencilState
         */
        virtual void SetDepthStencilState(IDepthStencilState* state) = 0;

        //////////////////////////////////////////////////////////////
        // 리소스 바인딩
        //////////////////////////////////////////////////////////////

        /**
         * @brief 텍스처를 지정 슬롯에 바인딩
         * @param slot 텍스처 슬롯 번호 (0부터 시작)
         * @param texture 바인딩할 텍스처 (nullptr이면 해당 슬롯 해제)
         * @see TDME::ITexture
         */
        virtual void SetTexture(uint32 slot, ITexture* texture) = 0;

        //////////////////////////////////////////////////////////////
        // 렌더링 설정
        //////////////////////////////////////////////////////////////

        /**
         * @brief 렌더링 설정 적용
         * @param settings 렌더링 설정
         * @see TDME::RenderSettings
         */
        virtual void ApplyRenderSettings(const RenderSettings& settings) = 0;

        //////////////////////////////////////////////////////////////
        // 스프라이트 랜더링
        //////////////////////////////////////////////////////////////

        /**
         * @brief 스프라이트 랜더링
         * @param sprite 스프라이트 파라미터
         * @see TDME::SpriteDesc
         */
        virtual void DrawSprite(const SpriteDesc& sprite) = 0;

        //////////////////////////////////////////////////////////////
        // 저수준 프리미티브 렌더링
        //////////////////////////////////////////////////////////////

        /**
         * @brief 정점 레이아웃 설정
         * @param layout 정점 레이아웃 (nullptr 면 해제)
         * @see TDME::IVertexLayout
         */
        virtual void SetVertexLayout(IVertexLayout* layout) = 0;

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
        virtual void DrawPrimitives(EPrimitiveType type, const void* vertices, uint32 vertexCount, uint32 stride) = 0;
    };
} // namespace TDME