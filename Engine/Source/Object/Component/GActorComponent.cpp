#include "pch.h"
#include "Engine/Object/Component/GActorComponent.h"

#include "Engine/Object/Actor/AActor.h"

namespace TDME
{
    GActorComponent::GActorComponent()
        : GameObject(), m_owner(nullptr), m_isActive(true)
    {
    }

    GActorComponent::~GActorComponent()
    {
        UnregisterComponent();
    }

    void GActorComponent::RegisterComponent(AActor* owner)
    {
        m_owner = owner;
    }

    void GActorComponent::UnregisterComponent()
    {
        m_owner = nullptr;
    }
} // namespace TDME