#include "GraphicsSystem.h"

#include "Graphics.h"
#include "Graphic.h"

#include "Colour.h"
#include "Shape.h"
#include "Texture.h"
#include "Window.h"
#include "Point.h"

relic::GraphicsSystem::GraphicsSystem(const framework::Window& window, const framework::Graphics& graphics)
    : f_graphics(graphics), f_window(window)
{
}

void relic::GraphicsSystem::doUpdates()
{
    handleMessages();

    // Clear screen with colour white
    f_graphics.clear({ 0xFF, 0xFF, 0xFF, 0xFF });

    // Get camera
    const framework::Shape camera = f_window.getCamera();

    // Iterate through the graphic list and draw them based on where camera is
    for (framework::Graphic* graphic : m_graphic_ptrs)
    {
        f_graphics.draw(graphic, camera.x, camera.y);
    }

    // Iterate through the gui graphic list and draw them based on where camera is
    for (framework::Graphic* graphic : m_gui_graphic_ptrs)
    {
        f_graphics.draw(graphic);
    }

    // Display
    f_graphics.display();
}

void relic::GraphicsSystem::handleMessage(const GraphicsMessage msg)
{
    switch (msg.type)
    {
    case GMessageType::load_texture:
    {
        m_asset_manager.addTexture(msg.string_1, f_graphics.createTexture(msg.string_2));
        break;
    }
    case GMessageType::load_font:
    {
        m_asset_manager.addFont(msg.string_1, f_graphics.createFont(msg.string_2, msg.num));
        break;
    }
    case GMessageType::assign_texture:
    {
        f_graphics.assignTexture(msg.graphic, m_asset_manager.getTexture(msg.string_1));
        break;
    }
    case GMessageType::assign_text:
    {
        framework::Texture* texture_ptr = nullptr;

        // Check for wrapped text
        if (msg.graphic->getShape().w == 0 && msg.graphic->getShape().h == 0)
        {
            texture_ptr = f_graphics.createTextTexture(msg.string_1, m_asset_manager.getFont(msg.string_2), msg.color);

            msg.graphic->setSize(texture_ptr->getWidth(), texture_ptr->getHeight());
        }
        else
        {
            texture_ptr = f_graphics.createWrappedTextTexture(msg.string_1, m_asset_manager.getFont(msg.string_2), msg.color, &msg.graphic->getShape());
        }

        f_graphics.assignTexture(msg.graphic, texture_ptr);

        break;
    }
    case GMessageType::show_graphic:
    {
        if (msg.graphic->getShape().is_screen_bound)
        {
            m_gui_graphic_ptrs.push_back(msg.graphic);
        }
        else
        {
            m_graphic_ptrs.push_back(msg.graphic);
        }

        break;
    }
    default: ;
    }
}

