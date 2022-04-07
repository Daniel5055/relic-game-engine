#include "Game.h"

#include <cassert>

#include "GraphicsComponent.h"
#include "InputComponent.h"
#include "PhysicsComponent.h"
#include "CoreComponent.h"

#include "Scene.h"

#include "LoggedGraphics.h"

#include "GridPhysicsEngine.h"

relic::Game::Game(Scene* starting_scene)
    : f_window("Relic", 640, 480, true)
    , f_graphics(f_window)
    , f_input()
    , f_physics(0.016, 128.0)
    , m_input(f_window, f_input)
    , m_graphics(f_window, f_graphics)
    , m_physics(new GridPhysicsEngine(f_physics))
    , m_object_manager(*this)
    , m_current_scene(starting_scene)
{

    // Setting game as receiver of messages from the systems that send messages
    m_input.addReceiver(this);
    m_physics.addReceiver(this);

    // Scene Configuration
    Scene::setObjectManager(&m_object_manager);
    Scene::setWindowSize(f_window.getWindowWidth(), f_window.getWindowHeight());

    starting_scene->initialise();
}

void relic::Game::update()
{
    MessageReceiver<GameMessage>::handleMessages();
    MessageReceiver<GraphicsMessage>::handleMessages();
    MessageReceiver<PhysicsMessage>::handleMessages();
    MessageReceiver<InputMessage>::handleMessages();

    // Update Systems
    m_graphics.update();
    m_physics.update();
    m_input.update();


    MessageReceiver<GameMessage>::handleMessages();
    MessageReceiver<GraphicsMessage>::handleMessages();
    MessageReceiver<PhysicsMessage>::handleMessages();
    MessageReceiver<InputMessage>::handleMessages();

    // Update Objects
    m_object_manager.updateObjects();

}

bool relic::Game::isGameOver() const
{
    return m_game_over;
}

void relic::Game::handleMessage(const PhysicsMessage msg)
{
    if (msg.is_sent_by_system)
    {
        // Directed to object, physics messages do not need to communicate with system for now
        assert(msg.object_id >= 0);
        m_object_manager.getObject(msg.object_id).pushExternalMessage(msg);
    }
    else
    {
        m_physics.receiveMessage(msg);
    }
}

void relic::Game::handleMessage(const InputMessage msg)
{
    if (msg.is_sent_by_system)
    {
        // Directed to object, else to game
        if (msg.object_id >= 0)
        {
            m_object_manager.getObject(msg.object_id).pushExternalMessage(msg);
        }
        else if (msg.type == IMessageType::exit_button_pressed)
        {
            m_game_over = true;
        }
    }
    else
    {
        m_input.receiveMessage(msg);
    }
}

void relic::Game::handleMessage(const GraphicsMessage msg)
{
    if (msg.is_sent_by_system)
    {
        // Directed to object, graphics messages do not need to communicate with system for now
        assert(msg.object_id >= 0);
        m_object_manager.getObject(msg.object_id).pushExternalMessage(msg);
    }
    else
    {
        m_graphics.receiveMessage(msg);
    }
}

void relic::Game::handleMessage(const GameMessage msg)
{
    // Game handles game messages
    if (!msg.is_sent_by_system)
    {
        switch (msg.type)
        {
        case GameMessageType::change_scene:
            // Clear all objects
            m_object_manager.clearSceneObjects();

            // Initialize new scene
            m_current_scene = std::unique_ptr<Scene>(msg.scene_ptr);
            m_current_scene->initialise();

            break;

        case GameMessageType::set_camera:
            f_window.setCamera(*msg.shape_ptr);

            break;

        case GameMessageType::delete_object:
            m_object_manager.deleteObject(msg.object_id);

            break;
        default:;
        }
    }
}

