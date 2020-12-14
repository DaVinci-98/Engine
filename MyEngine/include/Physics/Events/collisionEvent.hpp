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
        CollisionEvent(std::string& t_group, CollisionInfo t_info,
            std::shared_ptr<Body2D> t_dynamic, std::shared_ptr<Body2D> t_static) :
            m_physicsGroup(t_group), m_dynamicBody(t_dynamic), m_staticBody(t_static),  m_info(t_info) { }
            
        inline std::string group()
            { return m_physicsGroup; }
        inline std::shared_ptr<Body2D> dynamicBody()
            { return m_dynamicBody; }
        inline std::shared_ptr<Body2D> staticBody()
            { return m_staticBody; }
        inline CollisionInfo info()
            { return m_info; }

    private:
        CollisionInfo m_info;
        std::string m_physicsGroup;
        std::shared_ptr<Body2D> m_dynamicBody;
        std::shared_ptr<Body2D> m_staticBody;
    };
}