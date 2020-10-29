#include "platform.hpp"
#include "Glfw/Events/keyEvent.hpp"
#include "Glfw/Events/keyEventListener.hpp"

#include <iostream>

namespace
{
    void assignKeyMovement(std::shared_ptr<Platform>& t_platform, MyEngine::Glfw::Events::KeyEventListener& t_keyEventListener)
    {
        using MyEngine::Glfw::Events::KeyEvent;
        auto left    = [t_platform](KeyEvent &t_event) { t_platform->velocity() = glm::vec2(0,0); t_platform->acceleration() += glm::vec2(-400, 0);  t_event.handle(); };
        auto right   = [t_platform](KeyEvent &t_event) { t_platform->velocity() = glm::vec2(0,0); t_platform->acceleration() += glm::vec2( 400, 0);  t_event.handle(); };
        auto release = [t_platform](KeyEvent &t_event) { t_platform->velocity() = glm::vec2(0,0); t_platform->acceleration()  = glm::vec2( 0, 0);    t_event.handle(); };

        t_keyEventListener.registerKeyCallback(left,  KeyEvent::Key::KEY_LEFT,  KeyEvent::KeyMods::NONE, KeyEvent::KeyEventType::PRESSED);
        t_keyEventListener.registerKeyCallback(right, KeyEvent::Key::KEY_LEFT,  KeyEvent::KeyMods::NONE, KeyEvent::KeyEventType::RELEASED);
        t_keyEventListener.registerKeyCallback(right, KeyEvent::Key::KEY_RIGHT, KeyEvent::KeyMods::NONE, KeyEvent::KeyEventType::PRESSED);
        t_keyEventListener.registerKeyCallback(left,  KeyEvent::Key::KEY_RIGHT, KeyEvent::KeyMods::NONE, KeyEvent::KeyEventType::RELEASED);
    }

    void makeMesh(std::shared_ptr<MyEngine::Renderer::Mesh2D>& t_mesh, unsigned int t_width, unsigned int t_height)
    {
        if(!t_mesh)
        {
            MyEngine::Renderer::Triangle2D bottomLeft(0, 0, t_width, t_height, 0, 0);
            MyEngine::Renderer::Triangle2D topRight(t_width, t_width, 0, 0, t_height, t_height);

            t_mesh = std::make_shared<MyEngine::Renderer::Mesh2D>();
            t_mesh -> setTriangles(std::vector{ bottomLeft, topRight });
        }
    }

    void makeMaterial(std::shared_ptr<MyEngine::Renderer::Material>& t_material, MyEngine::Renderer::Renderer& t_renderer)
    {
        if(!t_material)
        {
            auto shader = t_renderer.shader(t_renderer.colourShader());
            t_material = std::make_shared<MyEngine::Renderer::Material>(shader);
            t_material->setColour(glm::vec4(0, 0, 0, 0));
        }
    }
}

std::shared_ptr<Platform> Platform::makePlatform(Platform::PlatformArgs& t_args)
{
    makeMesh(t_args.m_mesh, t_args.m_width, t_args.m_height);
    makeMaterial(t_args.m_material, t_args.m_renderer);

    auto platform = std::make_shared<Platform>(t_args.m_material, t_args.m_mesh);

    platform -> setAssociatedModel(platform -> modelMatrix());
    platform -> applyTranslation(glm::vec2(t_args.m_x, t_args.m_y));

    assignKeyMovement(platform, t_args.m_keyListener);

    return platform;
}

