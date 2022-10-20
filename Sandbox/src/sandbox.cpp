#include "sandbox.hpp"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/random.hpp>
#include <numeric>

void Sandbox::setupPlatform()
{
    unsigned int width  = 10 * m_blockSize;
    unsigned int height = 1.2 * m_blockSize;

    auto args = Platform::PlatformArgs{
        .m_x = (screenWidth() - width) / 2,
        .m_y = 2 * height,
        .m_width = width,
        .m_height = height,
        .m_material = m_material,
        .m_mesh = nullptr,
        .m_renderer = renderer(),
        .m_keyListener = keyEventListener(),
        .m_physics = physicsManager(),
    };

    m_platform = Platform::makePlatform(args);
    if(args.m_material && !m_material) m_material = args.m_material;

    physicsManager().addBody(m_windowGroup, m_platform);
    auto collisionCallback = [this](MyEngine::Physics::Events::CollisionEvent &t_event) 
    {
        t_event.callingBody() -> velocity() *= 0.0f;
        t_event.callingBody() -> applyTranslation(- t_event.info().m_penetration);
        t_event.handle();
    };
    physicsManager().registerCollisionCallback(m_windowGroup, collisionCallback, m_platform);
}

void Sandbox::addBall(unsigned int t_x, unsigned int t_y)
{
    auto args = Ball::BallArgs{
        .m_x = t_x,
        .m_y = t_y,
        .m_side = static_cast<unsigned int>(m_blockSize * 1.1),
        .m_material = m_ballMaterial,
        .m_mesh = m_ballMesh,
        .m_renderer = renderer(),
        .m_keyListener = keyEventListener(),
        .m_physics = physicsManager(),
    };
    auto ball = Ball::makeBall(args);
    if(args.m_material && !m_ballMaterial) m_ballMaterial = args.m_material;
    if(args.m_mesh && !m_ballMesh) m_ballMesh = args.m_mesh;

    auto windowCollisionCallback = [this](MyEngine::Physics::Events::CollisionEvent &t_event) 
    {
        t_event.callingBody() -> velocity() *= -0.5f;
        if(t_event.info().m_penetration.y != 0)
            t_event.callingBody() -> velocity()[0] *= -1;
        if(t_event.info().m_penetration.x != 0)
            t_event.callingBody() -> velocity()[1] *= -1;
        t_event.callingBody() -> applyTranslation(-t_event.info().m_penetration);

        t_event.handle();
    };
    auto paltformCollisionCallback = [this](MyEngine::Physics::Events::CollisionEvent &t_event) 
    {
        t_event.callingBody() -> velocity()[0] *= -1.0f;
        if(t_event.info().m_penetration.y != 0)
            t_event.callingBody() -> velocity()[0] *= -1;

        if(t_event.secondBody() -> velocity() != glm::vec2(0))
        {
            t_event.callingBody() -> velocity()[1] *= -1.5f;
            t_event.callingBody() -> velocity() += t_event.secondBody() -> velocity();
        }
        else
            t_event.callingBody() -> velocity()[1] *= -0.9f;

        t_event.handle();
    };
    auto blockCollisionCallback = [this](MyEngine::Physics::Events::CollisionEvent &t_event) 
    {
        t_event.callingBody() -> applyTranslation(-t_event.info().m_penetration);
        t_event.callingBody() -> velocity() *= -0.5f;
        if(t_event.info().m_penetration.y != 0)
            t_event.callingBody() -> velocity()[0] *= -1;
        
        auto hitBlock = std::find(this->m_breakableBlocks.begin(), this->m_breakableBlocks.end(), t_event.secondBody());
        if(hitBlock == this->m_breakableBlocks.end())
            this->physicsManager().removeBody(t_event.secondBody());
        else
            this->m_breakableBlocks[hitBlock - this->m_breakableBlocks.begin()] -> takeDamage(); 

        t_event.handle();
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
    physicsManager().registerCollisionCallback(m_breakableBlockGroup,      blockCollisionCallback,    ball);
    physicsManager().registerCollisionCallback(m_windowGroup,     windowCollisionCallback,   ball);

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

    auto args = BreakableBlock::BreakableBlockArgs{
        .m_x = GL_SHADING_RATE_1_INVOCATION_PER_4X2_PIXELS_NV,
        .m_y = y,
        .m_width = width,
        .m_height = height,
        .m_material = m_material,
        .m_mesh = mesh,
        .m_renderer = renderer(),
        .m_physics = physicsManager(),
    };

    for(std::size_t i = 0; i < 3; i++)
    {
        for(std::size_t ii = 0; ii < maxBlocks; ii++)
        {
            args.m_x = x;
            args.m_y = y;
            auto breakableBlock = BreakableBlock::makeBreakableBlock(args);
            m_breakableBlocks.push_back(breakableBlock);
            physicsManager().addBody(m_breakableBlockGroup, m_breakableBlocks.back());

            x += 1 + width;
        }
        if(args.m_material && !m_material) m_material = args.m_material;
        if(args.m_mesh && !mesh) mesh = args.m_mesh;


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

    m_maxBallCount     -> setFont("/home/DaVinci/Projects/Engine/Sandbox/res/fonts/font_0.png", 
                                  "/home/DaVinci/Projects/Engine/Sandbox/res/fonts/font.fnt", 
                                  renderer().shader(renderer().textureShader()));
    m_ballCount        -> setFont("/home/DaVinci/Projects/Engine/Sandbox/res/fonts/font_0.png", 
                                  "/home/DaVinci/Projects/Engine/Sandbox/res/fonts/font.fnt", 
                                  renderer().shader(renderer().textureShader()));
    m_currentScoreText -> setFont("/home/DaVinci/Projects/Engine/Sandbox/res/fonts/font_0.png", 
                                  "/home/DaVinci/Projects/Engine/Sandbox/res/fonts/font.fnt", 
                                  renderer().shader(renderer().textureShader()));
    m_maxScoreText     -> setFont("/home/DaVinci/Projects/Engine/Sandbox/res/fonts/font_0.png", 
                                  "/home/DaVinci/Projects/Engine/Sandbox/res/fonts/font.fnt", 
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
    auto spawnBall = [this](KeyEvent &t_event) 
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

        t_event.handle(); 
    };
    keyEventListener().registerKeyCallback(spawnBall, 
        KeyEvent::Key::KEY_R, 
        KeyEvent::KeyMods::NONE, 
        KeyEvent::KeyEventType::PRESSED);

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
        addToRenderQueue(ball, nullptr);
    for(auto& breakableBlock : m_breakableBlocks)
        addToRenderQueue(breakableBlock, breakableBlock->getRenderCallback());
    addToRenderQueue(m_platform, m_platform->getRenderCallback());
    addToRenderQueue(m_ballCount, nullptr);
    addToRenderQueue(m_maxBallCount, nullptr);
    addToRenderQueue(m_maxScoreText, nullptr);
    addToRenderQueue(m_currentScoreText, nullptr);

    return true;
}