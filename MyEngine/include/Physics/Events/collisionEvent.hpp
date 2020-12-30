#pragma once

#include "EventSystem/event.hpp"
#include "Physics/body2D.hpp"

#include <memory>
#include <tuple>
#include <glm/glm.hpp>

namespace MyEngine::Physics
{
    class CollisionEvent : public EventSystem::Event<CollisionEvent>
    {
    public:
        CollisionEvent(std::string& t_group, CollisionInfo& t_info,
            std::shared_ptr<Body2D> t_calling, std::shared_ptr<Body2D> t_second) :
            m_physicsGroup(t_group), m_callingBody(t_calling), m_secondBody(t_second),  m_info(t_info) { }
            
        inline std::string group()
            { return m_physicsGroup; }
        inline std::shared_ptr<Body2D> callingBody()
            { return m_callingBody; }
        inline std::shared_ptr<Body2D> secondBody()
            { return m_secondBody; }
        inline CollisionInfo& info()
            { return m_info; }

    private:
        CollisionInfo m_info;
        std::string m_physicsGroup;
        std::shared_ptr<Body2D> m_callingBody;
        std::shared_ptr<Body2D> m_secondBody;
    };
}