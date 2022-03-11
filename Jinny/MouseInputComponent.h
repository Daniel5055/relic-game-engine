#pragma once

#include "InputComponent.h"

namespace Jinny
{
	class MouseInputComponent : public InputComponent
	{
	public:
		MouseInputComponent();

		// Initialization
		void initialize(GameObject& object);

		// Updating
		void update();

		// Closing
		void close();

	private:
		// Message Handling from input
		virtual void handleMessages();

		// --- Data ---
		bool m_mouse_button_down;
	};


}