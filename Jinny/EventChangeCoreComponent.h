#pragma once

#include "CoreComponent.h"

#include "ObjectInput.h"

namespace Jinny
{

	class Scene;

	class EventChangeCoreComponent : public CoreComponent
	{
	public:

		// Constructor
		EventChangeCoreComponent(ObjectInput trigger_input, Scene* new_scene);

		// Updating
		virtual void update();
	private:

		// Event Handling
		virtual void handleEvents();

		// --- Data ---

		// Scene to change to
		Scene* m_next_scene;
		const ObjectInput m_trigger_input;

	};
}