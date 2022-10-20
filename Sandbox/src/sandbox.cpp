#include "sandbox.hpp"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/random.hpp>
#include <numeric>

void Sandbox::setupPlatform()
{
    unsigned int width  = 10 * m_blockSize;
    unsigned int height = 1.2 * m_blockSize;
    unsigned int x = (screenWidth() - width) / 2;
    unsigned int y = 2 * height;
    std::shared_ptr<MyEngine::Renderer::Mesh2D> mesh = nullptr;

    renderer().colourShader();

    m_platform = Platform::makePlatform(m_material, mesh, 
                                        renderer().shader(renderer().colourShader()),
                                        x, y, width, height);

    physicsManager().addBody(m_windowGroup, m_platform);
    auto collisionCallback = [this](MyEngine::Physics::CollisionInfo& t_info, 
                                    std::shared_ptr<MyEngine::Physics::Body2D> t_first, 
                                    std::shared_ptr<MyEngine::Physics::Body2D> t_second) 
    {
        t_first -> velocity() *= 0.0f;
        t_first -> applyTranslation(- t_info.m_penetration);
    };
    physicsManager().registerCollisionCallback(m_windowGroup, collisionCallback, m_platform);

    using MyEngine::Glfw::Events::KeyEvent;
    auto left    = [this](KeyEvent &&t_event) 
        { m_platform -> velocity() = glm::vec2(0,0); m_platform -> acceleration() += glm::vec2(-400, 0); };
    auto right   = [this](KeyEvent &&t_event) 
        { m_platform -> velocity() = glm::vec2(0,0); m_platform -> acceleration() += glm::vec2( 400, 0); };
    auto release = [this](KeyEvent &&t_event) 
        { m_platform -> velocity() = glm::vec2(0,0); m_platform -> acceleration()  = glm::vec2( 0, 0);   };

    registerKeyCallback(left,  std::make_tuple(KeyEvent::KeyMods::NONE, KeyEvent::Key::KEY_A, KeyEvent::KeyEventType::PRESSED));
    registerKeyCallback(right, std::make_tuple(KeyEvent::KeyMods::NONE, KeyEvent::Key::KEY_A, KeyEvent::KeyEventType::RELEASED));
    registerKeyCallback(right, std::make_tuple(KeyEvent::KeyMods::NONE, KeyEvent::Key::KEY_D, KeyEvent::KeyEventType::PRESSED));
    registerKeyCallback(left,  std::make_tuple(KeyEvent::KeyMods::NONE, KeyEvent::Key::KEY_D, KeyEvent::KeyEventType::RELEASED));
}

void Sandbox::addBall(unsigned int t_x, unsigned int t_y)
{
    unsigned int side = m_blockSize * 1.1;
    auto ball = Ball::makeBall(m_ballMaterial, m_ballMesh, 
                               renderer().shader(renderer().textureShader()), physicsManager(), 
                               t_x, t_y, side);

    auto windowCollisionCallback = [this](MyEngine::Physics::CollisionInfo& t_info, 
                                          std::shared_ptr<MyEngine::Physics::Body2D> t_first, 
                                          std::shared_ptr<MyEngine::Physics::Body2D> t_second) 
    {
        t_first -> velocity() *= -0.5f;
        if(t_info.m_penetration.y != 0)
            t_first -> velocity()[0] *= -1;
        if(t_info.m_penetration.x != 0)
            t_first -> velocity()[1] *= -1;
        t_first -> applyTranslation(-t_info.m_penetration);
    };
    auto paltformCollisionCallback = [this](MyEngine::Physics::CollisionInfo& t_info, 
                                            std::shared_ptr<MyEngine::Physics::Body2D> t_first, 
                                            std::shared_ptr<MyEngine::Physics::Body2D> t_second) 
    {
        t_first -> velocity()[0] *= -1.0f;
        if(t_info.m_penetration.y != 0)
            t_first -> velocity()[0] *= -1;

        if(t_second -> velocity() != glm::vec2(0))
        {
            t_first -> velocity()[1] *= -1.5f;
            t_first -> velocity() += t_second -> velocity();
        }
        else
            t_first -> velocity()[1] *= -0.9f;
    };
    auto blockCollisionCallback = [this](MyEngine::Physics::CollisionInfo& t_info, 
                                         std::shared_ptr<MyEngine::Physics::Body2D> t_first, 
                                         std::shared_ptr<MyEngine::Physics::Body2D> t_second) 
    {
        t_first -> applyTranslation(-t_info.m_penetration);
        t_first -> velocity() *= -0.5f;
        if(t_info.m_penetration.y != 0)
            t_first -> velocity()[0] *= -1;
        
        auto hitBlock = std::find(this -> m_breakableBlocks.begin(), this -> m_breakableBlocks.end(), t_second);
        if(hitBlock == this -> m_breakableBlocks.end())
            this -> physicsManager().removeBody(t_second);
        else
            this -> m_breakableBlocks[hitBlock - this -> m_breakableBlocks.begin()] -> takeDamage(); 
    };
    std::string platformBallGroup = "Platform-Ball-" + std::to_string(m_lastId++);

    physicsManager().registerPhysicsGroup(platformBallGroup, false);
    physicsManager().getGroup(platformBallGroup).setCollisionDetectionPipeline(
        std::vector<MyEngine::Physics::CollisionLevel>{MyEngine::Physics::CollisionLevel::AXIS_ALIGNED_BOUNDING_BOX});

    physicsManager().addBody(m_breakableBlockGroup, ball);
    physicsManager().addBody(platformBallGroup, ball);
    physicsManager().addBody(m_windowGroup, ball);
    physicsManager().addBody(platformBallGroup, m_platform);

    physicsManager().registerCollisionCallback(platformBallGroup, paltformCollisionCallback, ball);
    physicsManager().registerCollisionCallback(m_breakableBlockGroup, blockCollisionCallback, ball);
    physicsManager().registerCollisionCallback(m_windowGroup, windowCollisionCallback, ball);

    m_balls.push_back(ball);
    m_ballGroups.push_back(platformBallGroup);
}

void Sandbox::setupBlocks()
{
    unsigned int width  = 6 * m_blockSize;
    unsigned int height = 3 * m_blockSize;

    unsigned int maxBlocks = screenWidth() / width;
    unsigned int allign = (screenWidth() - maxBlocks * width - maxBlocks + 1) / 2;
    unsigned int y = screenHeight() - height - 1;
    unsigned int x = allign;

    std::shared_ptr<MyEngine::Renderer::Mesh2D> mesh;
    physicsManager().registerPhysicsGroup(m_breakableBlockGroup, true);
    physicsManager().getGroup(m_breakableBlockGroup).setCollisionDetectionPipeline(
    std::vector<MyEngine::Physics::CollisionLevel>{MyEngine::Physics::CollisionLevel::AXIS_ALIGNED_BOUNDING_BOX});

    for(std::size_t i = 0; i < 3; i++)
    {
        for(std::size_t ii = 0; ii < maxBlocks; ii++)
        {
            auto breakableBlock = BreakableBlock::makeBreakableBlock(
                m_material, mesh, renderer().shader(renderer().colourShader()), physicsManager(),
                x, y, width, height);
            m_breakableBlocks.push_back(breakableBlock);
            physicsManager().addBody(m_breakableBlockGroup, m_breakableBlocks.back());

            x += 1 + width;
        }

        x = allign;
        y -= 1 + height;
    }
}

void Sandbox::setupText()
{
    m_maxBallCount     = std::make_shared<MyEngine::Renderer::Text>();
    m_ballCount        = std::make_shared<MyEngine::Renderer::Text>();
    m_currentScoreText = std::make_shared<MyEngine::Renderer::Text>();
    m_maxScoreText     = std::make_shared<MyEngine::Renderer::Text>();

    m_maxBallCount     -> setFont("/home/davinci/Projects/Engine/Sandbox/res/fonts/font_0.png", 
                                  "/home/davinci/Projects/Engine/Sandbox/res/fonts/font.fnt", 
                                  renderer().shader(renderer().textureShader()));
    m_ballCount        -> setFont("/home/davinci/Projects/Engine/Sandbox/res/fonts/font_0.png", 
                                  "/home/davinci/Projects/Engine/Sandbox/res/fonts/font.fnt", 
                                  renderer().shader(renderer().textureShader()));
    m_currentScoreText -> setFont("/home/davinci/Projects/Engine/Sandbox/res/fonts/font_0.png", 
                                  "/home/davinci/Projects/Engine/Sandbox/res/fonts/font.fnt", 
                                  renderer().shader(renderer().textureShader()));
    m_maxScoreText     -> setFont("/home/davinci/Projects/Engine/Sandbox/res/fonts/font_0.png", 
                                  "/home/davinci/Projects/Engine/Sandbox/res/fonts/font.fnt", 
                                  renderer().shader(renderer().textureShader()));

    m_currentScoreText -> setText("Current Score: ");
    m_maxScoreText     -> setText("Max Score: ");
    m_ballCount        -> setUint(1);
    m_maxBallCount     -> setUint(1);

    m_currentScoreText -> scale(m_blockSize * 6.0f, m_blockSize);
    m_maxScoreText     -> scale(m_blockSize * 4.5f, m_blockSize);
    m_ballCount        -> scale(m_blockSize * 0.5f, m_blockSize);
    m_maxBallCount     -> scale(m_blockSize * 0.5f, m_blockSize);

    m_currentScoreText -> translate(glm::vec2(0, m_blockSize * 1.1f));
    m_ballCount        -> translate(glm::vec2(m_blockSize * 8, m_blockSize * 1.1f));
    m_maxBallCount     -> translate(glm::vec2(m_blockSize * 6, 0));
}

void Sandbox::setupWindowCollision()
{
    auto vertices = 
    { 
        glm::vec2(0, 0), 
        glm::vec2(0, screenHeight()), 
        glm::vec2(screenWidth(), screenHeight()), 
        glm::vec2(screenWidth(), 0)
    };
    m_windowHitbox = std::make_shared<MyEngine::Physics::Body2D>(std::move(vertices), false);

    physicsManager().registerPhysicsGroup(m_windowGroup, true);
    physicsManager().getGroup(m_windowGroup).setCollisionDetectionPipeline(
        std::vector<MyEngine::Physics::CollisionLevel>{MyEngine::Physics::CollisionLevel::OUT_OF_BOUNDS});
    physicsManager().addBody(m_windowGroup, m_windowHitbox);
}

bool Sandbox::onWindowCreate()
{
    m_blockSize = std::gcd(screenHeight(), screenWidth()) / 16;
    
    setupWindowCollision();
    setupPlatform();
    setupBlocks();
    addBall((screenWidth() - m_blockSize) / 2, static_cast<unsigned int>(screenHeight()/2));

    using MyEngine::Glfw::Events::KeyEvent;
    auto spawnBall = [this](KeyEvent &&t_event) 
    {
        while(!this->m_breakableBlocks.empty())
        {
            physicsManager().removeBody(this->m_breakableBlocks.front());
            m_breakableBlocks.erase(m_breakableBlocks.begin());
        }
        while(!this->m_balls.empty())
        {
            physicsManager().removeBody(m_balls.front());
            m_balls.erase(m_balls.begin());
            physicsManager().unregisterPhysicsGroup(std::string(m_ballGroups.front()));
            m_ballGroups.erase(m_ballGroups.begin());
        }
        this -> setupBlocks();
        this -> addBall((this->screenWidth() - m_blockSize) / 2, static_cast<unsigned int>(screenHeight()/2));
        auto dX = this->screenWidth()/2.0f - this->m_platform->center().x;
        this -> m_platform -> applyTranslation(glm::vec2(dX, 0));
        m_ballCount -> setUint(m_balls.size());
    };
    registerKeyCallback(spawnBall, std::make_tuple(KeyEvent::KeyMods::NONE, KeyEvent::Key::KEY_R, KeyEvent::KeyEventType::PRESSED));

    setupText();

    return true;
}

bool Sandbox::onUpdate(float t_deltaTime)
{
    auto size = m_balls.size();
    for(std::size_t i = 0; i < size; i++)
    {
        if(glm::abs(m_balls[i] -> velocity().y) < 1.0f && 
           m_balls[i] -> center().y < m_blockSize)
        {
            physicsManager().removeBody(m_balls[i]);
            m_balls.erase(m_balls.begin() + i);
            physicsManager().unregisterPhysicsGroup(std::string(m_ballGroups[i]));
            m_ballGroups.erase(m_ballGroups.begin() + i);
            
            size--;
            i--;
            m_ballCount -> setUint(m_balls.size());
        }
    }

    size = m_breakableBlocks.size();
    for(std::size_t i = 0; i < size; i++)
    {
        if(m_breakableBlocks[i] -> health() == 0)
        {
            physicsManager().removeBody(m_breakableBlocks[i]);
            addBall(m_breakableBlocks[i] -> center().x, m_breakableBlocks[i] -> center().y);
            m_breakableBlocks.erase(m_breakableBlocks.begin() + i);

            size--;
            i--;
            m_ballCount -> setUint(m_balls.size());
            if(m_balls.size() > m_maxScore)
            {
                m_maxScore = m_balls.size();
                m_maxBallCount -> setUint(m_maxScore);
            }
        }
    }

    return true;
}

bool Sandbox::onRender()
{
    using MyEngine::Renderer::Drawable2D;
    for(auto& ball : m_balls)
        renderer().draw(*std::dynamic_pointer_cast<Drawable2D>(ball));
    for(auto& breakableBlock : m_breakableBlocks)
    {
        breakableBlock -> updateColour();
        renderer().draw(*std::dynamic_pointer_cast<Drawable2D>(breakableBlock));
    }
    // m_platform -> updateColour();
    renderer().draw(*std::dynamic_pointer_cast<Drawable2D>(m_platform));
    renderer().draw(*std::dynamic_pointer_cast<Drawable2D>(m_ballCount));
    renderer().draw(*std::dynamic_pointer_cast<Drawable2D>(m_maxBallCount));
    renderer().draw(*std::dynamic_pointer_cast<Drawable2D>(m_maxScoreText));
    renderer().draw(*std::dynamic_pointer_cast<Drawable2D>(m_currentScoreText));

    return true;
}