#pragma once

#include <Core/Types/Color.h>

#include <Engine/Object/Actor/AActor.h>

namespace TDME
{
    class GSceneComponent;
    class Shape2DRenderer;

    class APlanet : public AActor
    {
    public:
        APlanet();
        ~APlanet() override = default;

        //////////////////////////////////////////////////////////////
        // 라이프 사이클
        //////////////////////////////////////////////////////////////

        void Update(float deltaTime) override;
        void Render(Shape2DRenderer& renderer);

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
        GSceneComponent* GetOrbitOffsetComponent() const { return m_orbitOffset; }

        /**
         * @brief 행성 Body 컴포넌트 반환
         * @return GSceneComponent* 행성 Body 컴포넌트a
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

    private:
        GSceneComponent* m_orbit       = nullptr; // 공전 회전
        GSceneComponent* m_orbitOffset = nullptr; // 공전 반경 오프셋
        GSceneComponent* m_body        = nullptr; // 자전 및 행성 몸체

        float m_bodyRadius = 0.0f;          // 행성 반지름
        Color m_color      = Colors::WHITE; // 행성 색상

        float m_orbitSpeed = 0.0f; // 궤도 속도
        float m_spinSpeed  = 0.0f; // 자전 속도
    }; // class APlanet
} // namespace TDME