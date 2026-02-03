#pragma once

#include <Core/CoreTypes.h>

namespace TDME
{
    /**
     * @brief 게임 오브젝트 클래스
     * @details 게임 오브젝트를 관리하는 클래스.
     */
    class GameObject
    {
    public:
        GameObject();
        virtual ~GameObject() = default;

        //////////////////////////////////////////////////////////////
        // Getter / Setter
        //////////////////////////////////////////////////////////////

        /**
         * @brief 객체 ID 반환
         * @details 객체 ID는 객체가 생성될 때 자동으로 부여되며, 객체가 소멸될 때까지 유지됨
         * @return uint32 객체 ID
         */
        [[nodiscard]] uint32 GetObjectID() const { return m_objectID; }

        /**
         * @brief 객체 이름 설정
         * @param name 객체 이름
         */
        void SetName(const string& name) { m_name = name; }

        /**
         * @brief 객체 이름 설정
         * @param name 객체 이름
         */
        void SetName(string&& name) { m_name = std::move(name); }

        /**
         * @brief 객체 이름 반환
         * @return const string& 객체 이름
         */
        [[nodiscard]] const string& GetName() const { return m_name; }

        //////////////////////////////////////////////////////////////
        // 복사/이동 금지 (각 객체는 고유 ID를 가지고 있어야 함)
        //////////////////////////////////////////////////////////////
        GameObject(const GameObject&)            = delete;
        GameObject& operator=(const GameObject&) = delete;
        GameObject(GameObject&&)                 = delete;
        GameObject& operator=(GameObject&&)      = delete;

    protected:
        uint32 m_objectID = 0;
        string m_name;

    private:
        static uint32 s_nextObjectID;

    }; // class GameObject
} // namespace TDME