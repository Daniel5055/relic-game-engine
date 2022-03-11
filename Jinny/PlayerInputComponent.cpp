#include "PlayerInputComponent.h"

void Jinny::PlayerInputComponent::initialize(GameObject& object)
{
	setObject(&object);

	InputMessage msg;
	msg.type = IMessageType::SUBSCRIBE_INPUT;
	msg.object_ID = object.getObjectID();

	ObjectInput input;
	input.type = ObjectInputType::KEY_PRESS;

	input.key = 'a';
	msg.object_input = input;
	pushMessage(msg);

	m_keys_down['a'] = false;

	input.key = 'd';
	msg.object_input = input;
	pushMessage(msg);

	m_keys_down['d'] = false;

	input.key = 'w';
	msg.object_input = input;
	pushMessage(msg);

	m_keys_down['w'] = false;

	input.key = 's';
	msg.object_input = input;
	pushMessage(msg);

	m_keys_down['s'] = false;

}

void Jinny::PlayerInputComponent::update()
{
	handleMessages();
}

void Jinny::PlayerInputComponent::handleMessages()
{
	for (InputMessage msg = popMessage(); msg.type != IMessageType::NULL_MESSAGE; msg = popMessage())
	{
		switch (msg.type)
		{
		case IMessageType::INPUT_TRIGGERED:
			if (msg.object_input.type == ObjectInputType::KEY_DOWN)
			{
				if (m_keys_down[msg.object_input.key] == false)
				{
					m_keys_down[msg.object_input.key] = true;

					ObjectEvent o_event = { EventType::INPUT_TRIGGERED };
					o_event.input = msg.object_input;
					getObject()->pushEvent(o_event);

				}
			}
			else
			{
				m_keys_down[msg.object_input.key] = false;

				ObjectEvent o_event = { EventType::INPUT_TRIGGERED };
				o_event.input = msg.object_input;
				getObject()->pushEvent(o_event);
			}
			
			
			break;
		}
	}
}
