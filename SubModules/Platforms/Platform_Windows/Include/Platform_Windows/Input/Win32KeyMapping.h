#pragma once

#include <Engine/Input/Key.h>

#include <Windows.h>

namespace TDME
{
    /**
     * @brief Virtual Key를 Key로 변환
     * @param virtualKey Windows VK 코드
     * @return Key 대응하는 Key (없으면 EKeys::Invalid)
     * @see TDME::EKeys
     */
    const Key& VKToKey(UINT virtualKey);

    /**
     * @brief Key를 Virtual Key로 변환
     * @param key Key
     * @return UINT Windows VK 코드
     * @see TDME::Key
     */
    UINT KeyToVK(const Key& key);

} // namespace TDME