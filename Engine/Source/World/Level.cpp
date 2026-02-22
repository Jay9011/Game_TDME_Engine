#include "pch.h"
#include "Engine/World/Level.h"

#include "Engine/Object/IRenderable.h"
#include "Engine/Object/Actor/AActor.h"

#include <algorithm>
#include <memory>

namespace TDME
{
    Level::Level() = default;
    Level::~Level()
    {
        for (std::unique_ptr<AActor>& actor : m_actors)
        {
            actor->EndPlay();
        }
    }

    void Level::Update(float deltaTime)
    {
        FlushPendingDestroy();

        for (std::unique_ptr<AActor>& actor : m_actors)
        {
            actor->Update(deltaTime);
        }
    }

    void Level::Render()
    {
        for (std::unique_ptr<AActor>& actor : m_actors)
        {
            if (IRenderable* renderable = dynamic_cast<IRenderable*>(actor.get()))
            {
                renderable->Render();
            }
        }
    }

    //////////////////////////////////////////////////////////////
    // Actor 관리
    //////////////////////////////////////////////////////////////

    void Level::DestroyActor(AActor* actor)
    {
        if (!actor)
            return;

        // 중복 등록 방지
        auto it = std::find(m_pendingDestroy.begin(), m_pendingDestroy.end(), actor);
        if (it == m_pendingDestroy.end())
        {
            m_pendingDestroy.push_back(actor);
        }
    }

    //////////////////////////////////////////////////////////////
    // Private
    //////////////////////////////////////////////////////////////

    void Level::FlushPendingDestroy()
    {
        if (m_pendingDestroy.empty())
            return;

        // 1. EndPlay 호출
        for (AActor* actor : m_pendingDestroy)
        {
            actor->EndPlay();
        }

        // 2. erase remove 패턴으로 일괄 제거
        auto newEnd = std::remove_if(m_actors.begin(), m_actors.end(),
                                     [this](const std::unique_ptr<AActor>& owned)
                                     {
                                         return m_pendingDestroy.end() != std::find(m_pendingDestroy.begin(), m_pendingDestroy.end(), owned.get());
                                     });

        m_actors.erase(newEnd, m_actors.end());
        m_pendingDestroy.clear();
    }

} // namespace TDME