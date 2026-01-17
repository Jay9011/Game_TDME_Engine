#pragma once

#include "Platform_Windows/IWin32MessageProcessor.h"

#include <Core/Math/TVector2.h>
#include <Engine/Input/IInputDevice.h>
#include <Engine/Input/Key.h>

#include <Windows.h>
#include <unordered_set>

namespace TDME
{
    class Win32Input : public IInputDevice, public IWin32MessageProcessor
    {
    public:
        Win32Input()           = default;
        ~Win32Input() override = default;

        /**
         * @brief 입력 장치를 초기화합니다.
         * @param window 입력 받을 Window 객체
         * @return true 성공, false 실패
         */
        bool Initialize(IWindow* window) override;

        void Update() override;

        //////////////////////////////////////////////////////////////
        // 키 입력 이벤트
        //////////////////////////////////////////////////////////////
        /**
         * @brief 키가 눌려있는지 확인합니다.
         * @param key 키
         * @return true/false
         */
        bool IsKeyDown(const Key& key) const override;

        /**
         * @brief 이번 프레임에 키가 눌려졌는지 확인합니다.
         * @param key 키
         * @return true/false
         */
        bool IsKeyPressed(const Key& key) const override;

        /**
         * @brief 이번 프레임에 키가 떼어졌는지 확인합니다.
         * @param key 키
         * @return true/false
         */
        bool IsKeyReleased(const Key& key) const override;

        //////////////////////////////////////////////////////////////
        // 마우스
        //////////////////////////////////////////////////////////////
        /**
         * @brief 마우스의 현재 위치를 반환합니다.
         * @return Vector2 마우스의 현재 위치
         */
        Vector2 GetAxis2D(const Key& axis) const override;

        /**
         * @brief 마우스의 현재 입력 값을 반환합니다.
         * @param axis 축
         * @return float 축의 현재 값
         */
        float GetAxisValue(const Key& axis) const override;

        //////////////////////////////////////////////////////////////
        // Win32 Event Handle
        //////////////////////////////////////////////////////////////
        /**
         * @brief Windows 키 눌림 이벤트 처리
         * @param key 눌린 키
         */
        void OnKeyDown(const Key& key);

        /**
         * @brief Windows 키 떼어짐 이벤트 처리
         * @param key 떼어진 키
         */
        void OnKeyUp(const Key& key);

        /**
         * @brief Windows 마우스 이동 이벤트 처리
         * @param x 마우스 X 좌표
         * @param y 마우스 Y 좌표
         */
        void OnMouseMove(int32 x, int32 y);

        /**
         * @brief Win32 메시지 처리
         * @param hWnd 윈도우 핸들
         * @param message 메시지
         * @param wParam 추가 매개변수
         * @param lParam 추가 매개변수
         * @param outResult 처리 결과 (처리한 경우에만 유효)
         * @return true 처리 완료, false 처리 안 함
         */
        bool ProcessMessage(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam, LRESULT& outResult) override;

    private:
        HWND m_hWnd = nullptr; // Windows 창 핸들

        std::unordered_set<Key> m_currentKeys;
        std::unordered_set<Key> m_previousKeys;

        Vector2 m_mousePosition;
    };
} // namespace TDME