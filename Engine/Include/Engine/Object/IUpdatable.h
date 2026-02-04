#pragma once

namespace TDME
{
    /**
     * @brief 업데이트 가능 인터페이스
     * @details 매 프레임 Update가 호출되는 객체를 위한 인터페이스
     */
    class IUpdatable
    {
    public:
        virtual ~IUpdatable() = default;

        /**
         * @brief 매 프레임 호출
         * @param deltaTime 이전 프레임과의 시간 차이 (초)
         */
        virtual void Update(float deltaTime) = 0;
    };
} // namespace TDME