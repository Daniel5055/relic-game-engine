#include "Game.h"

#include "GraphicsSystem.h"
#include "Scene.h"
#include "GridPhysicsEngine.h"
#include "InputSystem.h"
#include "PhysicsSystem.h"
#include "LoggingSystem.h"

relic::Game::Game(Scene* starting_scene)
    : MessageReceiver<GameSystemType>(Identifier::null)
    , f_window("Relic", 640, 480, true)
    , f_graphics(f_window)
    , f_input()
    , f_physics(0.016, 128.0)
    , m_current_scene(starting_scene)
{

    // Add systems
    m_systems.push_back(std::make_unique<InputSystem>(f_window, f_input));
    m_systems.push_back(std::make_unique<GraphicsSystem>(f_window, f_graphics));
    m_systems.push_back(std::make_unique<PhysicsSystem>(new GridPhysicsEngine(f_physics)));
    m_systems.push_back(std::make_unique<LoggingSystem>());

    // Scene Configuration
    Scene::setWindowSize(f_window.getWindowWidth(), f_window.getWindowHeight());

    Scene::setObjectManager(&m_object_manager);

    starting_scene->initialise();
}

void relic::Game::update()
{
    // Update Systems
    for (const auto& game_system : m_systems)
    {
        game_system->update();
    }

    // Handling messages sent to game
    handleMessages();

    // Update Objects
    m_object_manager.updateObjects();
}

bool relic::Game::isGameOver() const
{
    return m_game_over;
}

void relic::Game::handleMessage(const Message<GameSystemType>& msg)
{
    switch (msg.type)
    {
    case GameSystemType::exit_pressed:

        m_game_over = true;
        break;
    case GameSystemType::change_scene: 
        m_object_manager.clearSceneObjects();
        m_current_scene = std::unique_ptr<Scene>(std::any_cast<Scene*>(msg.value));
        m_current_scene->initialise();
        break;
    case GameSystemType::set_camera: break;
    case GameSystemType::delete_object: break;
    default: ;
    }
}
