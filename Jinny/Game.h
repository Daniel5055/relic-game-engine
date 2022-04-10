#pragma once

// Including framework
#include "Window.h"
#include "Input.h"
#include "Core.h"
#include "Physics.h"
#include "LoggedGraphics.h"

#include "MessageReceiver.h"
#include "GameType.h"

// Including systems

#include "GameObjectManager.h"
#include "GameSystem.h"

namespace relic
{
    class Scene;

    /**
     * \brief The backbone of the game engine, declaring all the framework classes and systems.
     * This class calls all the game loop related methods to the systems
     */
    class Game final
        : public MessageReceiver<GameSystemType>
    {
    public:
        // Constructor
        explicit Game(Scene* starting_scene = nullptr);

        void update();

        // Game Over Check
        bool isGameOver() const;

    private:
        // Handling game messages
        void handleMessage(const Message<GameSystemType>& msg) override;

        // Framework References
        const framework::Core f_core;
        framework::Window f_window;
        const framework::LoggedGraphics f_graphics;
        const framework::Input f_input;
        const framework::Physics f_physics;

        // Game Systems
        std::vector<std::unique_ptr<GameSystem>> m_systems{};

        // Object Manager
        GameObjectManager m_object_manager;

        // --- data ---
        bool m_game_over{false};

        std::unique_ptr<Scene> m_current_scene{};
    };
}
