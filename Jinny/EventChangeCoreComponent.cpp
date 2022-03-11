#include "EventChangeCoreComponent.h"

Jinny::EventChangeCoreComponent::EventChangeCoreComponent(ObjectInput trigger_input, Scene* new_scene)
	:m_next_scene(new_scene), m_trigger_input(trigger_input)
{
}

void Jinny::EventChangeCoreComponent::update()
{
	handleEvents();
}

void Jinny::EventChangeCoreComponent::handleEvents()
{
	for (auto it = getObject()->getQueueIterator(); it != getObject()->getQueueEnd(); it++)
	{
		switch (it->type)
		{
		case EventType::INPUT_TRIGGERED:

			// Check if required input
			if (it->input.type == m_trigger_input.type && it->input.key == m_trigger_input.key)
			{
				// Send message to core system to change event
				GameMessage msg;
				msg.type = GameMessageType::CHANGE_SCENE;
				msg.scene_ptr = m_next_scene;
				pushMessage(msg);
			}
			break;
		}
	}
}
