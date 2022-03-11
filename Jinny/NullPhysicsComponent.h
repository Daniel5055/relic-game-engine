#pragma once

#include "PhysicsComponent.h"

namespace Jinny
{
	class NullPhysicsComponent : public PhysicsComponent
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