#include "pch.h"
#include "Engine/World/World.h"

namespace TDME
{
    World::World()
        : m_persistentLevel(std::make_unique<Level>())
    {
    }

    World::~World() = default;

    void World::Update(float deltaTime)
    {
        m_persistentLevel->Update(deltaTime);
    }

    void World::Render()
    {
        m_persistentLevel->Render();
    }

    void World::DestroyActor(AActor* actor)
    {
        m_persistentLevel->DestroyActor(actor);
    }
} // namespace TDME