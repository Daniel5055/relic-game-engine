#pragma once

#include "GameSystem.h"

// Include messaging
#include "MessageBoard.h"
#include "GraphicsMessage.h"
#include "InputMessage.h"
#include "PhysicsMessage.h"
#include "GameMessage.h"

// Framework decleration
namespace Framework
{
	class Window;
	class Input;
	class Core;
	class Graphics;
	class Physics;
}

namespace Jinny
{
	class GameObjectManager;
	class Scene;

	// System decleration
	class PhysicsSystem;
	class GraphicsSystem;
	class InputSystem;


	/// <summary>
	/// This System is the core of the game
	///	It links all the systems together and connects messaging
	/// </summary>

	class Game
	{
	public:
		// Constructor
		Game();

		void initialize(Scene* starting_scene);
		void update();
		void close();

		// Destructor
		~Game();

		// Game Over Check
		bool isGameOver();

	private:
		void handleMessages();

		// Framework pointers
		Framework::Graphics* f_graphics;
		Framework::Core* f_core;
		Framework::Window* f_window;
		Framework::Input * f_input;
		Framework::Physics* f_physics;
		
		// Game System pointers
		InputSystem * m_input;
		GraphicsSystem* m_graphics;
		PhysicsSystem* m_physics;

		// Message Board pointers
		MessageBoard<GraphicsMessage>* m_graphics_message_board;
		MessageBoard<InputMessage>* m_input_message_board;
		MessageBoard<PhysicsMessage>* m_physics_message_board;
		MessageBoard<GameMessage> * m_core_message_board;
		
		// Object Manager pointer
		GameObjectManager* m_objectManager;

		// --- data ---
		bool m_game_over;
		Scene* m_current_scene;
	};
}