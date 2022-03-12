#include "GraphicsSystem.h"

#include "AssetManager.h"

#include "Graphics.h"
#include "Graphic.h"

#include "Color.h"
#include "Shape.h"
#include "Texture.h"
#include "Window.h"
#include "Point.h"

Jinny::GraphicsSystem::GraphicsSystem()
{
	// Nullptr
	m_asset_manager = nullptr;
	m_message_board = nullptr;
	f_graphics = nullptr;
	f_window = nullptr;
}

void Jinny::GraphicsSystem::initialize(Framework::Window* window, Framework::Graphics* graphics, MessageBoard<GraphicsMessage>* message_board)
{
	// Framework
	f_graphics = graphics;
	f_window = window;

	m_message_board = message_board;

	m_asset_manager = new AssetManager();

}

void Jinny::GraphicsSystem::update()
{
	handleMessages();

	// Clear screen with colour white
	f_graphics->clear({ 0xFF, 0xFF, 0xFF, 0xFF });

	// Get camera
	Framework::Shape* camera = f_window->getCamera();

	// Iterate through the graphic list and draw them based on where camera is
	for (Framework::Graphic* graphic : m_graphic_ptrs)
	{
		f_graphics->draw(graphic, camera->x, camera->y);
	}

	// Iterate through the gui graphic list and draw them based on where camera is
	for (Framework::Graphic* graphic : m_gui_graphic_ptrs)
	{
		f_graphics->draw(graphic);
	}

	// Display
	f_graphics->display();
}

void Jinny::GraphicsSystem::close()
{
	
}

Jinny::GraphicsSystem::~GraphicsSystem()
{
	delete m_asset_manager;
	m_asset_manager = nullptr;
}

void Jinny::GraphicsSystem::handleMessages()
{
	int size = m_message_board->getQueueSize();
	for (int it = 0; it < size; it++)
	{
		GraphicsMessage msg = m_message_board->popMessage();
		switch (msg.type)
		{
		case GMessageType::LOAD_TEXTURE:
		{
			m_asset_manager->addTexture(msg.string_1, f_graphics->createTexture(msg.string_2));
			break;
		}
		case GMessageType::LOAD_FONT:
		{
			m_asset_manager->addFont(msg.string_1, f_graphics->createFont(msg.string_2, msg.num));
			break;
		}
		case GMessageType::ASSIGN_TEXTURE:
		{
			f_graphics->assignTexture(msg.graphic, m_asset_manager->getTexture(msg.string_1));
			break;
		}
		case GMessageType::ASSIGN_TEXT:
		{
			Framework::Texture* texture_ptr = nullptr;

			// Check for wrapped text
			if (msg.graphic->getShape()->w == 0 && msg.graphic->getShape()->h == 0)
			{
				texture_ptr = f_graphics->createTextTexture(msg.string_1, m_asset_manager->getFont(msg.string_2), msg.color);

				msg.graphic->setSize(texture_ptr->getWidth(), texture_ptr->getHeight());
			}
			else
			{
				texture_ptr = f_graphics->createWrappedTextTexture(msg.string_1, m_asset_manager->getFont(msg.string_2), msg.color, msg.graphic->getShape());
			}

			f_graphics->assignTexture(msg.graphic, texture_ptr);

			break;
		}
		case GMessageType::SHOW_GRAPHIC:
		{
			if (msg.graphic->getShape()->is_screen_bound)
			{
				m_gui_graphic_ptrs.push_back(msg.graphic);
			}
			else
			{
				m_graphic_ptrs.push_back(msg.graphic);
			}

			break;
		}

		}
	}

}
