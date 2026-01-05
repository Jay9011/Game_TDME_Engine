#pragma once

#include "Core/CoreMacros.h"
#include "NameTypes.h"
#include <cstddef>

namespace TDME
{
    //////////////////////////////////////////////////////////////
    // 컴파일 타임 해시 함수 (DJB2, D.J. Bernstein's One-at-a-Time Hash 알고리즘)
    // 마법의 숫자 5381을 사용하여 해시값을 계산하며 각 문자를 한 번에 하나씩 처리하여 빠르게 해시값을 계산합니다.
    // 영문 소문자 문자열에 대해 충돌 가능성이 낮으며 비트 시프트와 덧셈 연산만 사용하여 빠르게 해시값을 계산합니다.
    // NOTE: 추가적인 정보 혹은 필요한 경우 공부 필요.
    //////////////////////////////////////////////////////////////

    /**
     * @brief 컴파일 타임 문자열 해시 함수
     * @param str 해시할 문자열
     * @return NameHash 해시값
     */
    FORCE_INLINE constexpr NameHash HashName(const char* str)
    {
        NameHash hash = 5381;
        while (*str)
        {
            hash = ((hash << 5) + hash) + static_cast<NameHash>(*str);
            ++str;
        }
        return hash;
    }

    //////////////////////////////////////////////////////////////
    // Name 구조체
    //////////////////////////////////////////////////////////////

    /**
     * @brief Name 구조체
     */
    struct Name
    {
    public:
        constexpr Name()
            : m_hash(NAME_INVALID_HASH)
#ifdef _DEBUG
              ,
              m_debugName(nullptr)
#endif
        {
        }

        constexpr Name(const char* name)
            : m_hash(name ? HashName(name) : NAME_INVALID_HASH)
#ifdef _DEBUG
              ,
              m_debugName(name)
#endif
        {
        }

        constexpr Name(NameHash hash, [[maybe_unused]] const char* debugName) // [[maybe_unused]] 미사용 경고 억제
            : m_hash(hash)
#ifdef _DEBUG
              ,
              m_debugName(debugName)
#endif
        {
        }

        //////////////////////////////////////////////////////////////
        // Getter / Setter
        //////////////////////////////////////////////////////////////

        [[nodiscard]] FORCE_INLINE constexpr bool IsValid() const { return m_hash != NAME_INVALID_HASH; } // [[nodiscard]] 반환값이 무시되는 경우 경고
        [[nodiscard]] FORCE_INLINE constexpr bool IsNone() const { return m_hash == NAME_INVALID_HASH; }  // [[nodiscard]] 반환값이 무시되는 경우 경고

        /**
         * @brief Name 해시 값을 반환
         * @return NameHash Name 해시 값
         */
        [[nodiscard]] FORCE_INLINE constexpr NameHash GetHash() const { return m_hash; }

        /**
         * @brief 디버그 모드인 경우 디버그 명을 반환
         * @note 디버그 모드가 아닌 경우 nullptr를 반환
         * @return const char* Name 문자열 (디버그 모드가 아닌 경우 nullptr)
         */
        [[nodiscard]] FORCE_INLINE constexpr const char* GetDebugName() const
        {
#ifdef _DEBUG
            return m_debugName;
#else
            return nullptr;
#endif
        }

        /**
         * @brief Name 문자열을 반환
         * @note 디버그 모드가 아닌 경우 "None"을 반환
         * @return const char* Name 문자열 (디버그 모드가 아닌 경우 "None")
         */
        [[nodiscard]] FORCE_INLINE constexpr const char* ToString() const
        {
#ifdef _DEBUG
            return m_debugName ? m_debugName : "None";
#else
            return "None";
#endif
        }

        //////////////////////////////////////////////////////////////
        // 연산자 오버로딩
        //////////////////////////////////////////////////////////////

        FORCE_INLINE constexpr bool operator==(const Name& other) const { return m_hash == other.m_hash; }
        FORCE_INLINE constexpr bool operator!=(const Name& other) const { return m_hash != other.m_hash; }
        FORCE_INLINE constexpr bool operator<(const Name& other) const { return m_hash < other.m_hash; }
        FORCE_INLINE constexpr bool operator>(const Name& other) const { return m_hash > other.m_hash; }
        FORCE_INLINE constexpr bool operator<=(const Name& other) const { return m_hash <= other.m_hash; }
        FORCE_INLINE constexpr bool operator>=(const Name& other) const { return m_hash >= other.m_hash; }

        /**
         * @brief Name 객체를 bool 타입으로 변환
         * @return bool Name 객체가 유효한지 여부
         */
        FORCE_INLINE constexpr explicit operator bool() const { return IsValid(); }

        //////////////////////////////////////////////////////////////
        // 멤버 변수
        //////////////////////////////////////////////////////////////

        static const Name None; // Name 형 상수 None 객체 (유효하지 않은 Name 객체)

    private:
        NameHash m_hash;

#ifdef _DEBUG
        const char* m_debugName;
#endif
    };

    //////////////////////////////////////////////////////////////
    // 매크로 및 리터럴
    //////////////////////////////////////////////////////////////

    /**
     * @brief Name 상수 정의 매크로 (엔진 내부에서 상수형 Name 객체를 정의할 때 사용할듯)
     */
#define DEFINE_NAME(str) ::TDME::Name(::TDME::HashName(str), str)

    /**
     * @brief Name 리터럴 연산자 오버로딩
     * @param str Name 문자열
     * @return Name Name 객체
     */
    constexpr Name operator""_name(const char* str, size_t)
    {
        return Name(str);
    }

} // namespace TDME

//////////////////////////////////////////////////////////////
// std::hash 템플릿 특수화 (unordered_map/set 지원)
// NOTE: 해시 자료구조에서 std::hash<T>를 Name 타입에 대해 특수화 하고 내부적으로 해시 함수를 사용할 때, operator() 오버로딩을 호출하여 해시값을 계산 시킴
//////////////////////////////////////////////////////////////

namespace std
{
    template <>
    struct hash<TDME::Name>
    {
        size_t operator()(const TDME::Name& name) const noexcept
        {
            return static_cast<size_t>(name.GetHash());
        }
    };
} // namespace std