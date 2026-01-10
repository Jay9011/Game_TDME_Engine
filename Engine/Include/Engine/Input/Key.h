#pragma once

#include <Core/CoreMacros.h>
#include <Core/String/Name.h>

#include "EKeyType.h"

namespace TDME
{
    /**
     * @brief Key 구조체
     * @details Unreal Engine 기반 Fkey 와 유사한 구조 (Name 기반 확장성 확보)
     */
    struct Key
    {
    public:
        constexpr Key()
            : m_keyName(), m_keyType(EKeyType::Keyboard)
        {
        }

        constexpr Key(const char* keyName, EKeyType keyType = EKeyType::Keyboard)
            : m_keyName(keyName), m_keyType(keyType)
        {
        }

        constexpr Key(Name keyName, EKeyType keyType = EKeyType::Keyboard)
            : m_keyName(keyName), m_keyType(keyType)
        {
        }

        //////////////////////////////////////////////////////////////
        // Getter / Setter
        //////////////////////////////////////////////////////////////

        [[nodiscard]] FORCE_INLINE constexpr bool        IsValid() const { return m_keyName.IsValid(); }
        [[nodiscard]] FORCE_INLINE constexpr EKeyType    GetKeyType() const { return m_keyType; }
        [[nodiscard]] FORCE_INLINE constexpr const Name& GetKeyName() const { return m_keyName; }
        [[nodiscard]] FORCE_INLINE const char*           ToString() const { return m_keyName.ToString(); }

        //////////////////////////////////////////////////////////////
        // KeyType 확인
        //////////////////////////////////////////////////////////////

        [[nodiscard]] FORCE_INLINE constexpr bool IsKeyboard() const { return m_keyType == EKeyType::Keyboard; }
        [[nodiscard]] FORCE_INLINE constexpr bool IsMouse() const { return m_keyType == EKeyType::Mouse || m_keyType == EKeyType::MouseAxis; }
        [[nodiscard]] FORCE_INLINE constexpr bool IsGamepad() const { return m_keyType == EKeyType::Gamepad || m_keyType == EKeyType::GamepadAxis; }
        [[nodiscard]] FORCE_INLINE constexpr bool IsTouch() const { return m_keyType == EKeyType::Touch; }
        [[nodiscard]] FORCE_INLINE constexpr bool IsAxis() const { return m_keyType == EKeyType::MouseAxis || m_keyType == EKeyType::GamepadAxis; }

        //////////////////////////////////////////////////////////////
        // 연산자 오버로딩
        //////////////////////////////////////////////////////////////

        FORCE_INLINE constexpr bool operator==(const Key& other) const { return m_keyName == other.m_keyName; }
        FORCE_INLINE constexpr bool operator!=(const Key& other) const { return m_keyName != other.m_keyName; }
        FORCE_INLINE constexpr bool operator<(const Key& other) const { return m_keyName < other.m_keyName; }
        FORCE_INLINE constexpr bool operator>(const Key& other) const { return m_keyName > other.m_keyName; }
        FORCE_INLINE constexpr bool operator<=(const Key& other) const { return m_keyName <= other.m_keyName; }
        FORCE_INLINE constexpr bool operator>=(const Key& other) const { return m_keyName >= other.m_keyName; }

        /**
         * @brief Key 객체를 bool 타입으로 변환
         * @return true Key 객체가 유효한지 여부
         * @return false Key 객체가 유효하지 않은지 여부
         */
        FORCE_INLINE constexpr explicit operator bool() const { return IsValid(); }

    private:
        Name     m_keyName;
        EKeyType m_keyType;
    };

    //////////////////////////////////////////////////////////////
    // 매크로 및 리터럴
    //////////////////////////////////////////////////////////////

#define DEFINE_KEY(name)          ::TDME::Key(DEFINE_NAME(#name), ::TDME::EKeyType::Keyboard)
#define DEFINE_MOUSE_KEY(name)    ::TDME::Key(DEFINE_NAME(#name), ::TDME::EKeyType::Mouse)
#define DEFINE_MOUSE_AXIS(name)   ::TDME::Key(DEFINE_NAME(#name), ::TDME::EKeyType::MouseAxis)
#define DEFINE_GAMEPAD_KEY(name)  ::TDME::Key(DEFINE_NAME(#name), ::TDME::EKeyType::Gamepad)
#define DEFINE_GAMEPAD_AXIS(name) ::TDME::Key(DEFINE_NAME(#name), ::TDME::EKeyType::GamepadAxis)
#define DEFINE_TOUCH_KEY(name)    ::TDME::Key(DEFINE_NAME(#name), ::TDME::EKeyType::Touch)

} // namespace TDME

//////////////////////////////////////////////////////////////
// std::hash 템플릿 특수화 (unordered_map/set 지원)
// NOTE: 해시 자료구조에서 std::hash<T>를 Name 타입에 대해 특수화 하고 내부적으로 해시 함수를 사용할 때, operator() 오버로딩을 호출하여 해시값을 계산 시킴
//////////////////////////////////////////////////////////////

namespace std
{
    template <>
    struct hash<TDME::Key>
    {
        size_t operator()(const TDME::Key& key) const noexcept
        {
            return static_cast<size_t>(key.GetKeyName().GetHash());
        }
    };
} // namespace std