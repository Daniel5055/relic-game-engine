#include "MouseInputComponent.h"


// Framework
#include "Shape.h"

Jinny::MouseInputComponent::MouseInputComponent()
{
	m_mouse_button_down = false;
}

void Jinny::MouseInputComponent::initialize(GameObject& object)
{
	setObject(&object);

	ObjectEvent o_event = *object.getQueueIterator();

	Framework::Shape* shape = nullptr;

	// Event should be initialization message
	if (o_event.type == EventType::OBJECT_INITIALIZATION_SHAPE)
	{
		shape = o_event.shape;
	}

	// Send Messages

	// General Message
	InputMessage msg;
	msg.type = IMessageType::SUBSCRIBE_INPUT;
	msg.object_ID = object.getObjectID();
	msg.object_shape = shape;

	
	ObjectInput o_i;

	// Object Input 1
	o_i.type = ObjectInputType::LEFT_MOUSE_PRESS;
	msg.object_input = o_i;

	pushMessage(msg);

	// Object Input 2
	msg.object_input.type = ObjectInputType::MOUSE_OVER;
	pushMessage(msg);
}

void Jinny::MouseInputComponent::update()
{
	handleMessages();
}

void Jinny::MouseInputComponent::close()
{
}

void Jinny::MouseInputComponent::handleMessages()
{
	for (InputMessage msg = popMessage(); msg.type != IMessageType::NULL_MESSAGE; msg = popMessage())
	{
		switch (msg.type)
		{
		case IMessageType::INPUT_TRIGGERED:

			ObjectEvent o_event(EventType::INPUT_TRIGGERED);
			ObjectInput o_input;

			// Mouse Clicking
			switch (msg.object_input.type)
			{
			case ObjectInputType::MOUSE_OVER:
				o_input.type = ObjectInputType::MOUSE_OVER;
				o_event.input = o_input;

				getObject()->pushEvent(o_event);
				break;

			case ObjectInputType::MOUSE_OFF:
				o_input.type = ObjectInputType::MOUSE_OFF;
				o_event.input = o_input;

				getObject()->pushEvent(o_event);

				m_mouse_button_down = false;
				break;

			case ObjectInputType::LEFT_MOUSE_DOWN:
				m_mouse_button_down = true;

				o_input.type = ObjectInputType::LEFT_MOUSE_DOWN;
				o_event.input = o_input;

				getObject()->pushEvent(o_event);

				break;

			case ObjectInputType::LEFT_MOUSE_UP:
				if (m_mouse_button_down)
				{
					o_input.type = ObjectInputType::LEFT_MOUSE_UP;
					o_event.input = o_input;

					getObject()->pushEvent(o_event);

					m_mouse_button_down = false;
				}

				break;
			}

			break;

		}


	}
}


