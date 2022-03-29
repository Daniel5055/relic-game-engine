#include "Game.h"

#include "GraphicsComponent.h"
#include "InputComponent.h"
#include "PhysicsComponent.h"
#include "CoreComponent.h"

#include "Scene.h"
#include "StartScene.h"

#include "LoggedGraphics.h"

#include "GridPhysicsEngine.h"

Jinny::Game::Game()
    :Game(nullptr)
{
}

Jinny::Game::Game(Scene* starting_scene)
    : m_current_scene(starting_scene)
    , m_game_over(false)
    , m_graphics_message_board()
    , m_input_message_board()
    , m_physics_message_board()
    , m_core_message_board()
    , m_object_manager()
    , f_core()
    , f_window("Relic", 640, 480, true)
    , f_input()
    , f_physics(0.016, 128.0)
    , f_graphics(f_window) 
    , m_input(f_window, f_input, m_input_message_board)
    , m_graphics(f_window, f_graphics, m_graphics_message_board)
    , m_physics(new GridPhysicsEngine(f_physics), m_physics_message_board)
{

    // Configuring Special Components with message boards
    InputComponent::setMessageBoard(&m_input_message_board);
    PhysicsComponent::setMessageBoard(&m_physics_message_board);
    CoreComponent::setMessageBoard(&m_core_message_board);
    GraphicsComponent::setMessageBoard(&m_graphics_message_board);

    // Scene Configuration
    Scene::setObjectManager(&m_object_manager);
    Scene::setWindowSize(f_window.getWindowWidth(), f_window.getWindowHeight());

    m_current_scene->initialize();
}

void Jinny::Game::update()
{
    // Update Systems
    m_graphics.update();
    m_physics.update();
    m_input.update();

    // Handle Messages sent to game
    handleMessages();

    // Update Objects
    m_object_manager.updateObjects();
}

Jinny::Game::~Game()
{
}

bool Jinny::Game::isGameOver()
{
    return m_game_over;
}

void Jinny::Game::handleMessages()
{
    // Send messages from the systems to the object components

    // TODO: Holy shit I can definetly optimise this

    // Send Input messages
    int size = m_input_message_board.getQueueSize();
    for (int i = 0; i < size; i++)
    {
        InputMessage msg = m_input_message_board.popMessage();
        if (msg.object_ID >= 0)
        {
            m_object_manager.getObject(msg.object_ID).recieveInputMessage(msg);
        }
        else
        {
            if (msg.type == IMessageType::EXIT_BUTTON_PRESSED)
            {
                m_game_over = true;
            }
        }
    }

    // Send Graphics messages
    size = m_graphics_message_board.getQueueSize();
    for (int i = 0; i < size; i++)
    {
        GraphicsMessage msg = m_graphics_message_board.popMessage();

        if (msg.object_ID >= 0)
        {
            m_object_manager.getObject(msg.object_ID).recieveGraphicsMessage(msg);
        }
    }

    // Send Physics Messages
    size = m_physics_message_board.getQueueSize();
    for (int i = 0; i < size; i++)
    {
        PhysicsMessage msg = m_physics_message_board.popMessage();

        if (msg.object_ID >= 0)
        {
            m_object_manager.getObject(msg.object_ID).recievePhysicsMessage(msg);
        }
    }

    // Messages to the game from objects
    size = m_core_message_board.getQueueSize();
    for (int i = 0; i < size; i++)
    {
        GameMessage msg = m_core_message_board.popMessage();
        switch (msg.type)
        {
        case GameMessageType::CHANGE_SCENE:

            // Clear all objects
            m_object_manager.clearSceneObjects();

            // Initialize new scene
            m_current_scene = std::unique_ptr<Scene>(msg.scene_ptr);
            m_current_scene->initialize();

            break;

        case GameMessageType::SET_CAMERA:
            f_window.setCamera(*msg.shape_ptr);

            break;

        case GameMessageType::DELETE_OBJECT:
            m_object_manager.deleteObject(msg.object_ID);

            break;
        }
    }

}
