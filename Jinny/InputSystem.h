#pragma once

#include <vector>
#include <map>
#include <utility>

#include "GameSystem.h"

#include "MessageBoard.h"
#include "InputMessage.h"



// Framework Dependencies
#include "Shape.h"

namespace Framework
{
	class Input;
	enum class MouseEvent;

	class Window;
}

namespace Jinny
{
	class InputSystem : public GameSystem
	{
	public:
		typedef std::pair<int, Framework::Shape*> InputData;

		// ctor
		InputSystem();

		// Initialization
		void initialize(Framework::Window* window, Framework::Input* input, MessageBoard<InputMessage>* message_board);

		// Update
		void update();

		// Close
		void close();

	private:
		// Virtual Overides for update function
		void handleMessages();

		// --- Framework ---
		Framework::Input* f_input;
		Framework::Window* f_window;

		// --- Data ---

		// Message Board
		MessageBoard<InputMessage>* m_message_board;
		
		// Input Subscriptions
		std::map<Framework::MouseEvent, std::vector<InputData>> m_mouse_button_subscriptions;

		std::map<InputData, bool> m_mouse_over_subscribtions;

		std::map<char, std::vector<int>> m_key_supscriptions;
	};
}



