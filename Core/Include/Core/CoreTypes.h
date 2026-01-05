#pragma once

#include <cstddef>
#include <cstdint>
#include <string>

namespace TDME
{
    //////////////////////////////////////////////////////////////
    // 정수 타입
    //////////////////////////////////////////////////////////////

    using int8  = std::int8_t;
    using int16 = std::int16_t;
    using int32 = std::int32_t;
    using int64 = std::int64_t;

    using uint8  = std::uint8_t;
    using uint16 = std::uint16_t;
    using uint32 = std::uint32_t;
    using uint64 = std::uint64_t;

    using uchar  = unsigned char;
    using ushort = unsigned short;
    using uint   = unsigned int;
    using ulong  = unsigned long;

    //////////////////////////////////////////////////////////////
    // 크기 타입
    //////////////////////////////////////////////////////////////

    using size_t = std::size_t;

    //////////////////////////////////////////////////////////////
    // 문자열 타입
    //////////////////////////////////////////////////////////////

    using string  = std::string;
    using wstring = std::wstring;

} // namespace TDME