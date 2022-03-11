#pragma once

#include "GraphicsComponent.h"

namespace Jinny
{
	class NullGraphicsComponent : public GraphicsComponent
	{
		// Initialization
		virtual void initialize(GameObject& object)
		{}

		// Updating
		virtual void update()
		{}

		// Closing
		virtual void close()
		{}
	};
}