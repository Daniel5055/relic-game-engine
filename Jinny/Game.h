#pragma once

// Include messaging
#include "MultiMessageReceiver.h"

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

namespace relic
{
    class Scene;

    /**
     * \brief The backbone of the game engine, declaring all the framework classes and systems.
     * This class calls all the game loop related methods to the systems
     */
    class Game final
        : public MultiMessageReceiver
    {
    public:
        // Constructor
        explicit Game(Scene* starting_scene = nullptr);

        void update();

        // Game Over Check
        bool isGameOver() const;

    private:
        // Handling messages sent between systems and components
        void handleMessage(PhysicsMessage msg) override;
        void handleMessage(InputMessage msg) override;
        void handleMessage(GraphicsMessage msg) override;

        // Handling messages sent by components to the game 
        void handleMessage(GameMessage msg) override;

        // Framework References
        const framework::Core f_core;
        framework::Window f_window;
        const framework::LoggedGraphics f_graphics;
        const framework::Input f_input;
        const framework::Physics f_physics;

        // Game System
        InputSystem m_input;
        GraphicsSystem m_graphics;
        PhysicsSystem m_physics;

        // Object Manager
        GameObjectManager m_object_manager;

        // --- data ---
        bool m_game_over{false};

        std::unique_ptr<Scene> m_current_scene;
    };
}
