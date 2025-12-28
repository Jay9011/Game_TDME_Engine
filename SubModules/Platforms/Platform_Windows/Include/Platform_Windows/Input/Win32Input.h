#pragma once

#include <Core/Math/TVector2.h>
#include <Engine/Input/IInputDevice.h>
#include <array>
#include <Windows.h>

namespace TDME
{
    class Win32Input : public IInputDevice
    {
    public:
        Win32Input();
        ~Win32Input() override = default;

        /**
         * @brief 입력 장치를 초기화합니다.
         * @param window 입력 받을 Window 객체
         * @return true 성공, false 실패
         */
        bool Initialize(IWindow* window) override;

        void Update() override;

        //////////////////////////////////////////////////////////////
        // 키보드
        //////////////////////////////////////////////////////////////
        /*
         * @brief 현재 키가 눌려있는지 확인합니다.
         * @param key 키 코드
         */
        bool IsKeyDown(EKeyCode key) const override;

        /**
         * @brief 이번 프레임에 키가 눌려졌는지 확인합니다.
         * @param key 키 코드
         */
        bool IsKeyPressed(EKeyCode key) const override;

        /**
         * @brief 이번 프레임에 키가 떼어졌는지 확인합니다.
         * @param key 키 코드
         */
        bool IsKeyReleased(EKeyCode key) const override;

        //////////////////////////////////////////////////////////////
        // 마우스
        //////////////////////////////////////////////////////////////
        /**
         * @brief 마우스의 현재 위치를 반환합니다.
         * @return Vector2 마우스의 현재 위치
         */
        Vector2 GetMousePosition() const override;

        /**
         * @brief 마우스 버튼이 눌려있는지 확인합니다.
         * @param button 마우스 버튼 코드
         */
        bool IsMouseButtonDown(EMouseButton button) const override;

        /**
         * @brief 이번 프레임에 마우스 버튼이 눌려졌는지 확인합니다.
         * @param button 마우스 버튼 코드
         */
        bool IsMouseButtonPressed(EMouseButton button) const override;

        /**
         * @brief 이번 프레임에 마우스 버튼이 떼어졌는지 확인합니다.
         * @param button 마우스 버튼 코드
         */
        bool IsMouseButtonReleased(EMouseButton button) const override;

    private:
        static constexpr size_t KEY_COUNT          = static_cast<size_t>(EKeyCode::COUNT);
        static constexpr size_t MOUSE_BUTTON_COUNT = static_cast<size_t>(EMouseButton::COUNT);

        HWND m_hWnd; // Windows 창 핸들

        std::array<bool, KEY_COUNT> m_currentKeys;
        std::array<bool, KEY_COUNT> m_previousKeys;

        std::array<bool, MOUSE_BUTTON_COUNT> m_currentMouseButtons;
        std::array<bool, MOUSE_BUTTON_COUNT> m_previousMouseButtons;

        Vector2 m_mousePosition;
    };
} // namespace TDME