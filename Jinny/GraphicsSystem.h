#pragma once

#include <vector>

#include "GameSystem.h"

#include "MessageBoard.h"
#include "GraphicsMessage.h"

#include "AssetManager.h"

// Framework Dependencies
namespace Framework
{
    class Graphics;
    class Graphic;
    class Window;
}

namespace Jinny
{
    struct GraphicsMessage;

    /**
     * System relating to graphics.
     * Uses the asset manager and graphics framework to load and store textures, retrieve textures and assign graphics,
     * and render the graphics.
     */
    class GraphicsSystem : public GameSystem
    {
    public:
        // constructor
        GraphicsSystem(const Framework::Window& t_window, const Framework::Graphics& t_graphics, MessageBoard<GraphicsMessage>& t_message_board);

        // Update
        void update();

    private:
        // --- Internal Functions ---

        // Message Handling
        void handleMessages();

        // --- Framework ---
        const Framework::Graphics& f_graphics;
        const Framework::Window& f_window;

        // --- Data ---

        // Jinny Dependencies
        AssetManager m_asset_manager;
        MessageBoard<GraphicsMessage>& m_message_board;

        // Render list
        std::vector<Framework::Graphic*> m_graphic_ptrs;
        std::vector<Framework::Graphic*> m_gui_graphic_ptrs;

    };
}
