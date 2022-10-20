#include "Application/MyEngine.hpp"
#include "Physics/body2D.hpp"
#include "Renderer/text.hpp"

#include "platform.hpp"
#include "ball.hpp"
#include "breakableBlock.hpp"

#include <glm/glm.hpp>
#include <memory>
#include <iostream>

#define STRINGIFY2(X) #X
#define STRINGIFY(X) STRINGIFY2(X)
#define PATH STRINGIFY(SANDBOX_PATH)

class Sandbox : public MyEngine::Application
{
public:
    Sandbox(std::string title, int w, int h) : 
        MyEngine::Application(title, w, h, false, false, 1 / 120.0f) { }

    bool onWindowCreate() override;
    bool onRender() override;
    bool onUpdate(float t_deltaTime) override;

private: 
    void setupPlatform();
    void setupBlocks();
    void addBall(unsigned int t_x, unsigned int t_y);
    void setupWindowCollision();
    void setupText();
    void setupPaths();

    unsigned int m_maxScore = 1;
    unsigned int m_blockSize;
    unsigned int m_lastId = 0;

    std::string m_ballTexturePath = "";
    std::string m_fontPngPath = "";
    std::string m_fontPath = "";

    std::shared_ptr<MyEngine::Renderer::Text> m_maxBallCount;
    std::shared_ptr<MyEngine::Renderer::Text> m_ballCount;
    std::shared_ptr<MyEngine::Renderer::Text> m_currentScoreText;
    std::shared_ptr<MyEngine::Renderer::Text> m_maxScoreText;


    std::shared_ptr<Platform> m_platform;
    std::vector<std::shared_ptr<Ball>> m_balls;
    std::vector<std::string> m_ballGroups;
    std::vector<std::shared_ptr<BreakableBlock>> m_breakableBlocks;

    std::shared_ptr<MyEngine::Renderer::Material> m_material;
    std::shared_ptr<MyEngine::Renderer::Material> m_ballMaterial;
    std::shared_ptr<MyEngine::Renderer::Mesh2D> m_ballMesh;

    std::string m_windowGroup = "window";
    std::string m_breakableBlockGroup = "Block-Ball";
    std::shared_ptr<MyEngine::Physics::Body2D> m_windowHitbox;
};


std::unique_ptr<MyEngine::Application> MyEngine::CreateApplication()
{
    return std::make_unique<Sandbox>("Very creative title!", 1080, 720);
}