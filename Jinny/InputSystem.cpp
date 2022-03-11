#include "InputSystem.h"

#include "Input.h"
#include "InputEvent.h"

#include "Point.h"
#include "Window.h"

Jinny::InputSystem::InputSystem()
{
	m_message_board = nullptr;

	// Framework
	f_input = nullptr;
	f_window = nullptr;
}

void Jinny::InputSystem::initialize(Framework::Window* window, Framework::Input* input, MessageBoard<InputMessage>* message_board)
{
	m_message_board = message_board;

	// Framework
	f_input = input;

	f_window = window;
}

void Jinny::InputSystem::update()
{
	handleMessages();

	// Event Polling
	while(true)
	{
		Framework::InputEvent e = f_input->pollEvent();
		if (e.type == Framework::InputEventType::NULL_EVENT)
		{
			break;
		}

		// Message Handling
		switch (e.type)
		{
		case Framework::InputEventType::EXIT_BUTTON_PRESSED:
		{
			InputMessage msg;
			msg.type = IMessageType::EXIT_BUTTON_PRESSED;

			m_message_board->pushMessage(msg);

			break;
		}
		case Framework::InputEventType::MOUSE_EVENT:
		{
			Framework::Point static_mouse_pos = f_window->getStaticMousePosition();
			Framework::Point camera_mouse_pos = f_window->getCameraMousePosition();


			// Check specifically for mouse motion
			if (e.mouse_event == Framework::MouseEvent::MOUSE_MOTION)
			{
				for (auto it = m_mouse_over_subscribtions.begin(); it != m_mouse_over_subscribtions.end(); it++)
				{
					// If it is HUD Object
					if (it->first.second->is_screen_bound)
					{
						if (f_input->isInBoundary(static_mouse_pos, *it->first.second))
						{
							it->second = true;

							// Send message to object
							InputMessage msg;
							msg.object_ID = it->first.first;
							msg.type = IMessageType::INPUT_TRIGGERED;
							msg.object_input = ObjectInput(ObjectInputType::MOUSE_OVER);
							m_message_board->pushMessage(msg);
						}
						else
						{
							// Check for mouse off
							if (it->second == true)
							{
								it->second = false;

								// Send message to object
								InputMessage msg;
								msg.object_ID = it->first.first;
								msg.type = IMessageType::INPUT_TRIGGERED;
								msg.object_input = ObjectInput(ObjectInputType::MOUSE_OFF);
								m_message_board->pushMessage(msg);
							}

						}
					}
					else
					{
						if (f_input->isInBoundary(camera_mouse_pos, *it->first.second))
						{
							it->second = true;

							// Send message to object
							InputMessage msg;
							msg.object_ID = it->first.first;
							msg.type = IMessageType::INPUT_TRIGGERED;
							msg.object_input = ObjectInput(ObjectInputType::MOUSE_OVER);
							m_message_board->pushMessage(msg);
						}
						else
						{
							// Check for mouse off
							if (it->second == true)
							{
								it->second = false;

								// Send message to object
								InputMessage msg;
								msg.object_ID = it->first.first;
								msg.type = IMessageType::INPUT_TRIGGERED;
								msg.object_input = ObjectInput(ObjectInputType::MOUSE_OFF);
								m_message_board->pushMessage(msg);
							}

						}
					}
					
				}

			}
			else
			{
				// Then do the rest
				for (auto it = m_mouse_button_subscriptions[e.mouse_event].begin(); it != m_mouse_button_subscriptions[e.mouse_event].end(); it++)
				{
					// Check if HUD Object
					if (it->second->is_screen_bound)
					{
						if (f_input->isInBoundary(static_mouse_pos, *it->second))
						{
							// Send message to object
							InputMessage msg;
							msg.object_ID = it->first;
							msg.type = IMessageType::INPUT_TRIGGERED;
							msg.object_input = ObjectInput((ObjectInputType)(e.mouse_event));
							m_message_board->pushMessage(msg);
						}
					}
					else
					{
						if (f_input->isInBoundary(camera_mouse_pos, *it->second))
						{
							// Send message to object
							InputMessage msg;
							msg.object_ID = it->first;
							msg.type = IMessageType::INPUT_TRIGGERED;
							msg.object_input = ObjectInput((ObjectInputType)(e.mouse_event));
							m_message_board->pushMessage(msg);
						}
					}
				}
			}

			break;
		}
		case Framework::InputEventType::KEY_DOWN:
		{
			for (auto it = m_key_supscriptions[e.key].begin(); it != m_key_supscriptions[e.key].end(); it++)
			{
				InputMessage msg;
				msg.object_ID = *it;
				msg.type = IMessageType::INPUT_TRIGGERED;
				msg.object_input = ObjectInput(ObjectInputType::KEY_DOWN, e.key);
				m_message_board->pushMessage(msg);
			}

			break;
		}
		case Framework::InputEventType::KEY_UP:
		{
			for (auto it = m_key_supscriptions[e.key].begin(); it != m_key_supscriptions[e.key].end(); it++)
			{
				InputMessage msg;
				msg.object_ID = *it;
				msg.type = IMessageType::INPUT_TRIGGERED;
				msg.object_input = ObjectInput(ObjectInputType::KEY_UP, e.key);
				m_message_board->pushMessage(msg);
			}

			break;
		}
		}
	}
}

void Jinny::InputSystem::close()
{
}


void Jinny::InputSystem::handleMessages()
{
	int size = m_message_board->getQueueSize();
	for (int it = 0; it < size; it++)
	{
		InputMessage msg = m_message_board->popMessage();
		switch (msg.type)
		{
		case IMessageType::SUBSCRIBE_INPUT:
			switch (msg.object_input.type)
			{
			case ObjectInputType::MOUSE_OVER:
				m_mouse_over_subscribtions[{msg.object_ID, msg.object_shape}] = false;
				break;
			case ObjectInputType::LEFT_MOUSE_PRESS:
				if (m_mouse_button_subscriptions.find(Framework::MouseEvent::LEFT_DOWN) != m_mouse_button_subscriptions.end())
				{
					m_mouse_button_subscriptions[Framework::MouseEvent::LEFT_DOWN].push_back({ msg.object_ID, msg.object_shape });
				}
				else
				{
					m_mouse_button_subscriptions[Framework::MouseEvent::LEFT_DOWN] = { { msg.object_ID, msg.object_shape } };
				}

				if (m_mouse_button_subscriptions.find(Framework::MouseEvent::LEFT_UP) != m_mouse_button_subscriptions.end())
				{
					m_mouse_button_subscriptions[Framework::MouseEvent::LEFT_UP].push_back({ msg.object_ID, msg.object_shape });
				}
				else
				{
					m_mouse_button_subscriptions[Framework::MouseEvent::LEFT_UP] = { { msg.object_ID, msg.object_shape } };
				}
				
				break;
			case ObjectInputType::RIGHT_MOUSE_PRESS:

				if (m_mouse_button_subscriptions.find(Framework::MouseEvent::RIGHT_DOWN) != m_mouse_button_subscriptions.end())
				{
					m_mouse_button_subscriptions[Framework::MouseEvent::RIGHT_DOWN].push_back({ msg.object_ID, msg.object_shape });
				}
				else
				{
					m_mouse_button_subscriptions[Framework::MouseEvent::RIGHT_DOWN] = { { msg.object_ID, msg.object_shape } };
				}

				if (m_mouse_button_subscriptions.find(Framework::MouseEvent::RIGHT_UP) != m_mouse_button_subscriptions.end())
				{
					m_mouse_button_subscriptions[Framework::MouseEvent::RIGHT_UP].push_back({ msg.object_ID, msg.object_shape });
				}
				else
				{
					m_mouse_button_subscriptions[Framework::MouseEvent::RIGHT_UP] = { { msg.object_ID, msg.object_shape } };
				}
				break;
			case ObjectInputType::KEY_PRESS:

				if (m_key_supscriptions.find(msg.object_input.key) != m_key_supscriptions.end())
				{
					m_key_supscriptions[msg.object_input.key].push_back(msg.object_ID);
				}
				else
				{
					m_key_supscriptions[msg.object_input.key] = { msg.object_ID };
				}
				break;
			}

			break;
		}
	}
}

