#pragma once

#include <vector>

#include "GameSystem.h"
#include "MessageReceiver.h"
#include "GraphicsType.h"
#include "AssetManager.h"

// Framework Dependencies
namespace framework
{
    class Graphics;
    class Graphic;
    class Window;
}

namespace relic
{
    /**
     * \brief System relating to graphics.
     * Uses the asset manager and graphics framework to load and store textures, retrieve textures and assign graphics,
     * and render the graphics.
     */
    class GraphicsSystem final :
        public GameSystem, 
        public MessageReceiver<GraphicsSystemType>
    {
    public:
        // constructor
        explicit GraphicsSystem(const framework::Window& window, const framework::Graphics& graphics);

    private:
        // --- Internal Functions ---
        void doUpdates() override;
        void handleMessage(Message<GraphicsSystemType> msg) override;

        // --- Framework ---
        const framework::Graphics& f_graphics;
        const framework::Window& f_window;

        // --- Data ---

        // Jinny Dependencies
        AssetManager m_asset_manager;

        // Render list
        std::vector<framework::Graphic*> m_graphic_ptrs;
        std::vector<framework::Graphic*> m_gui_graphic_ptrs;
    };
}
