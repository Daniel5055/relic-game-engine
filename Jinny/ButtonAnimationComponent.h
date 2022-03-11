#pragma once

#include "AnimationComponent.h"

namespace Jinny
{
	class ButtonAnimationComponent : public AnimationComponent
	{

	public:
		// Constructor
		ButtonAnimationComponent(GraphicsComponent* graphics_component, int texture_width, int texture_height);

		// --- pure virtual functions ---

			// Initialization
		void initialize(GameObject& object);

		// Updating
		void update();

		// Closing
		void close();

		// --- functions ---

	private:

		// Event Handling
		void handleEvents();
	};
}