#pragma once

#include <Core/Math/TVector2.h>

#include <Engine/Input/EKeyCode.h>
#include <Engine/Input/EMouseButton.h>

namespace TDME
{
    class IWindow;

    /**
     * @brief 입력 장치 인터페이스
     * @note 키보드, 마우스 등 입력 장치를 관리하는 인터페이스
     * @see TDME::IWindow
     */
    class IInputDevice
    {
    public:
        virtual ~IInputDevice() = default;

        /**
         * @brief 입력 장치를 초기화합니다.
         * @param window 입력 받을 Window 객체
         * @return true 성공, false 실패
         */
        virtual bool Initialize(IWindow* window) = 0;

        virtual void Update() = 0;

        //////////////////////////////////////////////////////////////
        // 키보드
        //////////////////////////////////////////////////////////////
        /*
         * @brief 현재 키가 눌려있는지 확인합니다.
         * @param key 키 코드
         */
        virtual bool IsKeyDown(EKeyCode key) const = 0;

        /**
         * @brief 이번 프레임에 키가 눌려졌는지 확인합니다.
         * @param key 키 코드
         */
        virtual bool IsKeyPressed(EKeyCode key) const = 0;

        /**
         * @brief 이번 프레임에 키가 떼어졌는지 확인합니다.
         * @param key 키 코드
         */
        virtual bool IsKeyReleased(EKeyCode key) const = 0;

        //////////////////////////////////////////////////////////////
        // 마우스
        //////////////////////////////////////////////////////////////
        /**
         * @brief 마우스의 현재 위치를 반환합니다.
         * @return Vector2 마우스의 현재 위치
         */
        virtual Vector2 GetMousePosition() const = 0;

        /**
         * @brief 마우스 버튼이 눌려있는지 확인합니다.
         * @param button 마우스 버튼 코드
         */
        virtual bool IsMouseButtonDown(EMouseButton button) const = 0;

        /**
         * @brief 이번 프레임에 마우스 버튼이 눌려졌는지 확인합니다.
         * @param button 마우스 버튼 코드
         */
        virtual bool IsMouseButtonPressed(EMouseButton button) const = 0;

        /**
         * @brief 이번 프레임에 마우스 버튼이 떼어졌는지 확인합니다.
         * @param button 마우스 버튼 코드
         */
        virtual bool IsMouseButtonReleased(EMouseButton button) const = 0;
    };
} // namespace TDME