#pragma once

#include "GameSystem.h"

// Include messaging
#include "MessageBoard.h"
#include "GraphicsMessage.h"
#include "InputMessage.h"
#include "PhysicsMessage.h"
#include "GameMessage.h"

// Including framework
#include "Window.h"
#include "Input.h"
#include "Core.h"
#include "Physics.h"
#include "Graphics.h"
#include "LoggedGraphics.h"

// Including systems
#include "GraphicsSystem.h"
#include "InputSystem.h"
#include "PhysicsSystem.h"

#include "GameObjectManager.h"

namespace Jinny
{
    class Scene;

    /**
     * The backbone of the game engine, declaring all the framework classes and systems.
     * This class calls all the game loop related methods to the systems
     */
    class Game
    {
    public:
        // Constructor
        Game();
        explicit Game(Scene* t_starting_scene = nullptr);

        void update();

        // Destructor
        ~Game();

        // Game Over Check
        bool isGameOver();

    private:
        void handleMessages();

        // Framework References
        const Framework::Core f_core;
        Framework::Window f_window;
        const Framework::LoggedGraphics f_graphics;
        const Framework::Input f_input;
        const Framework::Physics f_physics;

        // Game System pointers
        InputSystem m_input;
        GraphicsSystem m_graphics;
        PhysicsSystem m_physics;

        // Message Board pointers
        MessageBoard<GraphicsMessage> m_graphics_message_board;
        MessageBoard<InputMessage> m_input_message_board;
        MessageBoard<PhysicsMessage> m_physics_message_board;
        MessageBoard<GameMessage> m_core_message_board;

        // Object Manager pointer
        GameObjectManager m_object_manager;

        // --- data ---
        bool m_game_over;
        std::unique_ptr<Scene> m_current_scene;
    };
}