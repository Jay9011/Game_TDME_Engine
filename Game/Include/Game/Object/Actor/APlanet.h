#pragma once

#include <Core/Types/Color.h>

#include <Engine/Object/Actor/AActor.h>
#include <Engine/Object/IRenderable.h>

namespace TDME
{
    class ITexture;
    class GSceneComponent;
    class Shape3DRenderer;

    class APlanet : public AActor, public IRenderable
    {
    public:
        APlanet();
        ~APlanet() override = default;

        //////////////////////////////////////////////////////////////
        // 라이프 사이클
        //////////////////////////////////////////////////////////////

        void Update(float deltaTime) override;
        void Render() override;

        //////////////////////////////////////////////////////////////
        // 메서드들
        //////////////////////////////////////////////////////////////

        /**
         * @brief 다른 행성의 Body에 이 행성의 OrbitPivot을 부착
         * @param parent 부모 행성
         */
        void OrbitAround(APlanet* parent);

        //////////////////////////////////////////////////////////////
        // Getter / Setter
        //////////////////////////////////////////////////////////////

        /**
         * @brief 공전 반경 offset 컴포넌트 반환
         * @return GSceneComponent* 공전 반경 offset 컴포넌트 (자식 부착용)
         * @see TDME::GSceneComponent
         */
        [[nodiscard]] GSceneComponent* GetOrbitOffsetComponent() const { return m_orbitOffset; }

        /**
         * @brief 행성 Body 컴포넌트 반환
         * @return GSceneComponent* 행성 Body 컴포넌트
         * @see TDME::GSceneComponent
         */
        [[nodiscard]] GSceneComponent* GetBodyComponent() const { return m_body; }

        /**
         * @brief 궤도 속도 설정
         * @param speed 궤도 속도
         */
        void SetOrbitSpeed(float speed) { m_orbitSpeed = speed; }

        /**
         * @brief 자전 속도 설정
         * @param speed 자전 속도
         */
        void SetSpinSpeed(float speed) { m_spinSpeed = speed; }

        /**
         * @brief 궤도 반지름 설정
         * @param radius 궤도 반지름
         */
        void SetOrbitRadius(float radius);

        /**
         * @brief 행성 반지름 설정
         * @param radius 행성 반지름
         */
        void SetBodyRadius(float radius) { m_bodyRadius = radius; }

        /**
         * @brief 행성 색상 설정
         * @param color 행성 색상
         * @see TDME::Color
         */
        void SetColor(const Color& color) { m_color = color; }

        /**
         * @brief 행성 텍스처 설정
         * @param texture 행성 텍스처 (nullptr이면 색상 기반 렌더링)
         * @see TDME::ITexture
         */
        void SetTexture(ITexture* texture) { m_texture = texture; }

        /**
         * @brief 렌더러 설정
         * @param renderer 렌더러
         */
        void SetRenderer(Shape3DRenderer* renderer) { m_renderer = renderer; }

    private:
        GSceneComponent* m_orbit       = nullptr; // 공전 공간(Root Component)
        GSceneComponent* m_orbitOffset = nullptr; // 공전 반경 오프셋
        GSceneComponent* m_body        = nullptr; // 자전 및 행성 몸체

        float m_bodyRadius = 0.0f; // 행성 반지름
        float m_orbitSpeed = 0.0f; // 궤도 속도
        float m_spinSpeed  = 0.0f; // 자전 속도

        Color     m_color   = Colors::WHITE; // 행성 색상
        ITexture* m_texture = nullptr;       // 행성 텍스처

        Shape3DRenderer* m_renderer = nullptr;
    }; // class APlanet
} // namespace TDME