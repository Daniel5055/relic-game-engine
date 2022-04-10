#include "GraphicsSystem.h"

#include "Graphics.h"
#include "Graphic.h"

#include "Colour.h"
#include "Shape.h"
#include "Texture.h"
#include "Window.h"

relic::GraphicsSystem::GraphicsSystem(const framework::Window& window, const framework::Graphics& graphics)
    : MessageReceiver<GraphicsSystemType>(Identifier::null), f_graphics(graphics), f_window(window)
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

void relic::GraphicsSystem::handleMessage(const Message<GraphicsSystemType>& msg)
{
    switch (msg.type)
    {
    case GraphicsSystemType::load_texture:
    {
        const auto v = std::any_cast<std::pair<std::string, std::string>>(msg.value);
        m_asset_manager.addTexture(v.first, f_graphics.createTexture(v.second));
        break;
    }
    case GraphicsSystemType::load_font:
    {
        const auto v = std::any_cast<std::pair<std::string, std::pair<std::string, unsigned int>>>(msg.value);
        m_asset_manager.addFont(v.first, f_graphics.createFont(v.second.first, v.second.second));
        break;
    }
    case GraphicsSystemType::assign_texture:
    {
        const auto v = std::any_cast<std::pair<std::string, framework::Graphic*>>(msg.value);
        f_graphics.assignTexture(v.second, m_asset_manager.getTexture(v.first));
        break;
    }
    case GraphicsSystemType::assign_text:
    {
        framework::Texture* texture_ptr = nullptr;

        const auto v = std::any_cast<std::pair<std::pair<std::string, std::string>, std::pair<framework::Colour, framework::Graphic*>>>(msg.value);

        // Check for wrapped text
        if (v.second.second->getShape().w == 0 && v.second.second->getShape().h == 0)
        {
            texture_ptr = f_graphics.createTextTexture(v.first.first, m_asset_manager.getFont(v.first.second), v.second.first);

            v.second.second->setSize(texture_ptr->getWidth(), texture_ptr->getHeight());
        }
        else
        {
            texture_ptr = f_graphics.createWrappedTextTexture(v.first.first, m_asset_manager.getFont(v.first.second), v.second.first, &v.second.second->getShape());
        }

        f_graphics.assignTexture(v.second.second, texture_ptr);

        break;
    }
    case GraphicsSystemType::show_graphic:
    {
        const auto v = std::any_cast<framework::Graphic*>(msg.value);
        if (v->getShape().is_screen_bound)
        {
            m_gui_graphic_ptrs.push_back(v);
        }
        else
        {
            m_graphic_ptrs.push_back(v);
        }

        break;
    }
    case GraphicsSystemType::hide_graphic:
    {
        const auto v = std::any_cast<framework::Graphic*>(msg.value);

        bool erased = false;
        for (auto it = m_gui_graphic_ptrs.begin(); it != m_gui_graphic_ptrs.end(); ++it)
        {
            if (*it == v)
            {
                m_gui_graphic_ptrs.erase(it);
                erased = true;
                break;
            }
        }

        if (!erased)
        {
            for (auto it = m_graphic_ptrs.begin(); it != m_graphic_ptrs.end(); ++it)
            {
                if (*it == v)
                {
                    m_graphic_ptrs.erase(it);
                    erased = true;
                    break;
                }
            }

            if (!erased)
            {
                // TODO: ??
            }
        }

        break;
    }
    default:;
    }
}

