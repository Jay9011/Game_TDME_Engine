#pragma once

#include "Engine/Input/Key.h"

namespace TDME
{
    /**
     * @brief 애플리케이션 메시지 핸들러 인터페이스
     * @details OS 이벤트(키보드, 마우스, 게임패드 등)를 처리하는 인터페이스
     * @see https://github.com/EpicGames/UnrealEngine/blob/release/Engine/Source/Runtime/ApplicationCore/Public/GenericPlatform/GenericApplicationMessageHandler.h
     */
    class IApplicationMessageHandler
    {
    public:
        virtual ~IApplicationMessageHandler() = default;

        //////////////////////////////////////////////////////////////
        // 키보드 이벤트
        //////////////////////////////////////////////////////////////

        /**
         * @brief 키가 눌렸을 때 호출
         * @param key 눌린 키
         * @param characterCode 문자 코드 (텍스트 입력용, 0이면 비문자 입력)
         * @param isRepeat 반복 여부
         * @return true 이벤트 처리 성공, false 이벤트 처리 실패
         */
        virtual bool OnKeyDown(const Key& key, uint32 characterCode, bool isRepeat) { return false; }

        /**
         * @brief 키가 떼어졌을 때 호출
         * @param key 떼어진 키
         * @param characterCode 문자 코드 (텍스트 입력용, 0이면 비문자 입력)
         * @return true 이벤트 처리 성공, false 이벤트 처리 실패
         */
        virtual bool OnKeyUp(const Key& key, uint32 characterCode) { return false; }

        //////////////////////////////////////////////////////////////
        // 마우스 이벤트
        //////////////////////////////////////////////////////////////

        /**
         * @brief 마우스가 이동했을 때 호출
         * @param cursorX 마우스 커서 X 좌표
         * @param cursorY 마우스 커서 Y 좌표
         * @param deltaX 마우스 커서 X 좌표 변화량
         * @param deltaY 마우스 커서 Y 좌표 변화량
         * @return true 이벤트 처리 성공, false 이벤트 처리 실패
         */
        virtual bool OnMouseMove(int32 cursorX, int32 cursorY, int32 deltaX, int32 deltaY) { return false; }

        /**
         * @brief 마우스 버튼이 눌렸을 때 호출
         * @param button 눌린 마우스 버튼
         * @param cursorX 마우스 커서 X 좌표
         * @param cursorY 마우스 커서 Y 좌표
         * @return true 이벤트 처리 성공, false 이벤트 처리 실패
         */
        virtual bool OnMouseDown(const Key& button, int32 cursorX, int32 cursorY) { return false; }

        /**
         * @brief 마우스 버튼이 떼어졌을 때 호출
         * @param button 떼어진 마우스 버튼
         * @param cursorX 마우스 커서 X 좌표
         * @param cursorY 마우스 커서 Y 좌표
         * @return true 이벤트 처리 성공, false 이벤트 처리 실패
         */
        virtual bool OnMouseUp(const Key& button, int32 cursorX, int32 cursorY) { return false; }

        /**
         * @brief 마우스 버튼이 더블 클릭 되었을 때 호출
         * @param button 더블 클릭된 마우스 버튼
         * @param cursorX 마우스 커서 X 좌표
         * @param cursorY 마우스 커서 Y 좌표
         * @return true 이벤트 처리 성공, false 이벤트 처리 실패
         */
        virtual bool OnMouseDoubleClick(const Key& button, int32 cursorX, int32 cursorY) { return false; }

        /**
         * @brief 마우스 휠이 움직였을 때 호출
         * @param delta 마우스 휠 변화량 (양수: 위로, 음수: 아래로)
         * @param cursorX 마우스 커서 X 좌표
         * @param cursorY 마우스 커서 Y 좌표
         * @return true 이벤트 처리 성공, false 이벤트 처리 실패
         */
        virtual bool OnMouseWheel(float delta, int32 cursorX, int32 cursorY) { return false; }

        //////////////////////////////////////////////////////////////
        // 윈도우 이벤트
        //////////////////////////////////////////////////////////////

        /**
         * @brief 윈도우 크기가 변경될때 호출
         * @param width 윈도우 너비
         * @param height 윈도우 높이
         * @param wasMinimized 최소화에서 복원되었는지 여부
         * @return true 이벤트 처리 성공, false 이벤트 처리 실패
         */
        virtual void OnWindowResizing(int32 width, int32 height, bool wasMinimized) {}

        /**
         * @brief 윈도우가 이동되었을 때 호출
         * @param x 윈도우 X 좌표
         * @param y 윈도우 Y 좌표
         */
        virtual void OnWindowMoved(int32 x, int32 y) {}

        /**
         * @brief 윈도우가 포커스를 얻었을 때 호출
         */
        virtual void OnWindowFocusGained() {}

        /**
         * @brief 윈도우가 포커스를 잃었을 때 호출
         */
        virtual void OnWindowFocusLost() {}

        /**
         * @brief 윈도우 닫기 요청시
         */
        virtual bool OnWindowCloseRequested() { return false; }
    };
} // namespace TDME