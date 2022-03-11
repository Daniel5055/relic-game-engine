#pragma once

#include "CoreComponent.h"

namespace Jinny
{
	class NullCoreComponent : public CoreComponent
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
