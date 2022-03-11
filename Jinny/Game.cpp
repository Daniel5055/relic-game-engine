#include "Game.h"

#include "GraphicsSystem.h"
#include "InputSystem.h"
#include "PhysicsSystem.h"

#include "GraphicsComponent.h"
#include "InputComponent.h"
#include "PhysicsComponent.h"
#include "CoreComponent.h"

#include "Scene.h"
#include "StartScene.h"

#include "GameObjectManager.h"

#include "LoggedGraphics.h"
#include "Core.h"
#include "Window.h"
#include "Input.h"
#include "Physics.h"

Jinny::Game::Game()
{
	m_game_over = false;
	
	// Create MessageBoards which are going to be linked to the systems and components
	// Core System is in control of creation and disposal of message boards
	m_graphics_message_board = new MessageBoard<GraphicsMessage>();
	m_input_message_board = new MessageBoard<InputMessage>();
	m_physics_message_board = new MessageBoard<PhysicsMessage>();
	m_core_message_board = new MessageBoard<GameMessage>();

	// Game Systems created
	m_input = new InputSystem();
	m_graphics = new GraphicsSystem();
	m_physics = new PhysicsSystem();

	// Create Object Manager, which handles objects
	m_objectManager = new GameObjectManager();
	m_current_scene = nullptr;

	// Declare Frameworks
	f_graphics = new Framework::LoggedGraphics();
	f_core = new Framework::Core();
	f_window = new Framework::Window();
	f_input = new Framework::Input();
	f_physics = new Framework::Physics(0.016, 128.0, 0.25);
}

void Jinny::Game::initialize(Scene* starting_scene)
{
	// Initialize Systems with message boards and framework dependencies
	m_graphics->initialize(f_window, f_graphics, m_graphics_message_board);
	m_input->initialize(f_window, f_input, m_input_message_board);
	m_physics->intialize(f_physics, m_physics_message_board);

	// Configuring Special Components with message boards
	InputComponent::setMessageBoard(m_input_message_board);
	PhysicsComponent::setMessageBoard(m_physics_message_board);
	CoreComponent::setMessageBoard(m_core_message_board);
	GraphicsComponent::setMessageBoard(m_graphics_message_board);

	// Scene Configuration
	Scene::setObjectManager(m_objectManager);
	Scene::setWindowSize(f_window->getWindowWidth(), f_window->getWindowHeight());

	m_current_scene = starting_scene;
	m_current_scene->initialize();

	// Framework Initialization
	f_core->initialize();
	f_window->initialize("Window", 640, 480, true);
	f_graphics->initialize(f_window);

}

void Jinny::Game::update()
{
	// Update Systems
	m_graphics->update();
	m_physics->update();
	m_input->update();

	// Handle Messages sent to game
	handleMessages();

	// Update Objects
	m_objectManager->updateObjects();
}

void Jinny::Game::close()
{
	f_graphics->close();
	f_window->close();
	f_core->close();
}

Jinny::Game::~Game()
{
	// Delete Message Boards
	delete m_input_message_board;
	delete m_graphics_message_board;
	delete m_physics_message_board;
	delete m_core_message_board;

	// Delete Systems
	delete m_input;
	delete m_graphics;
	delete m_physics;

	// Delete Current Scene and object manager
	delete m_objectManager;
	delete m_current_scene;

	// Delete framework
	delete f_graphics;
	delete f_window;
	delete f_core;
	delete f_input;
	delete f_physics;
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
	int size = m_input_message_board->getQueueSize();
	for (int i = 0; i < size; i++)
	{
		InputMessage msg = m_input_message_board->popMessage();
		if (msg.object_ID >= 0)
		{
			m_objectManager->getObject(msg.object_ID)->recieveInputMessage(msg);
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
	size = m_graphics_message_board->getQueueSize();
	for (int i = 0; i < size; i++)
	{
		GraphicsMessage msg = m_graphics_message_board->popMessage();

		if (msg.object_ID >= 0)
		{
			m_objectManager->getObject(msg.object_ID)->recieveGraphicsMessage(msg);
		}
	}

	// Send Physics Messages
	size = m_physics_message_board->getQueueSize();
	for (int i = 0; i < size; i++)
	{
		PhysicsMessage msg = m_physics_message_board->popMessage();

		if (msg.object_ID >= 0)
		{
			m_objectManager->getObject(msg.object_ID)->recievePhysicsMessage(msg);
		}
	}

	// Messages to the game from objects
	size = m_core_message_board->getQueueSize();
	for (int i = 0; i < size; i++)
	{
		GameMessage msg = m_core_message_board->popMessage();
		switch (msg.type)
		{
		case GameMessageType::CHANGE_SCENE:

			// Delete first scene
			delete m_current_scene;

			// Clear all objects
			m_objectManager->clearSceneObjects();

			// Initialize new scene
			m_current_scene = msg.scene_ptr;
			m_current_scene->initialize();

			break;

		case GameMessageType::SET_CAMERA:
			f_window->setCamera(msg.shape_ptr);

			break;

		case GameMessageType::DELETE_OBJECT:
			m_objectManager->deleteObject(msg.object_ID);

			break;
		}
	}

}
