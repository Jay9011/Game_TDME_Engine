#include "pch.h"
#include "Engine/Object/GameObject.h"

namespace TDME
{
    uint32 GameObject::s_nextObjectID = 1;

    GameObject::GameObject()
        : m_objectID(s_nextObjectID++), m_name()
    {
    }
} // namespace TDME