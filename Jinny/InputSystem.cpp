#include "InputSystem.h"

#include "Input.h"
#include "InputEvent.h"

#include "Point.h"
#include "Window.h"

jinny::InputSystem::InputSystem(const framework::Window& window, const framework::Input& input)
    :f_input(input), f_window(window)
{
}

void jinny::InputSystem::doUpdates()
{
    handleMessages();

    // Event Polling
    while (true)
    {
        framework::InputEvent e = f_input.pollEvent();

        if (e.type == framework::InputEventType::null_event)
        {
            break;
        }

        // Message Handling, mainly reads messages and pushes it to the input systems
        switch (e.type)
        {
        case framework::InputEventType::exit_button_pressed:
        {
            InputMessage msg;
            msg.type = IMessageType::exit_button_pressed;
            msg.is_sent_by_system = true;

            sendMessage(msg);

            break;
        }
        case framework::InputEventType::mouse_event:
        {
            framework::Point static_mouse_pos = f_window.getStaticMousePosition();
            framework::Point camera_mouse_pos = f_window.getCameraMousePosition();


            // Check specifically for mouse motion
            if (e.mouse_event == framework::MouseEvent::mouse_motion)
            {
                for (auto it = m_mouse_over_subscriptions.begin(); it != m_mouse_over_subscriptions.end(); ++it)
                {
                    // If it is HUD Object
                    if (it->first.second->is_screen_bound)
                    {
                        if (f_input.isInBoundary(static_mouse_pos, *it->first.second))
                        {
                            it->second = true;

                            // Send message to object
                            InputMessage msg;
                            msg.object_id = it->first.first;
                            msg.type = IMessageType::input_triggered;
                            msg.object_input = ObjectInput(ObjectInputType::mouse_over);
                    msg.is_sent_by_system = true;
                            sendMessage(msg);
                        }
                        else
                        {
                            // Check for mouse off
                            if (it->second == true)
                            {
                                it->second = false;

                                // Send message to object
                                InputMessage msg;
                                msg.object_id = it->first.first;
                                msg.type = IMessageType::input_triggered;
                                msg.object_input = ObjectInput(ObjectInputType::mouse_off);
                    msg.is_sent_by_system = true;
                                sendMessage(msg);
                            }

                        }
                    }
                    else
                    {
                        if (f_input.isInBoundary(camera_mouse_pos, *it->first.second))
                        {
                            it->second = true;

                            // Send message to object
                            InputMessage msg;
                            msg.object_id = it->first.first;
                            msg.type = IMessageType::input_triggered;
                            msg.object_input = ObjectInput(ObjectInputType::mouse_over);
                    msg.is_sent_by_system = true;
                            sendMessage(msg);
                        }
                        else
                        {
                            // Check for mouse off
                            if (it->second == true)
                            {
                                it->second = false;

                                // Send message to object
                                InputMessage msg;
                                msg.object_id = it->first.first;
                                msg.type = IMessageType::input_triggered;
                                msg.object_input = ObjectInput(ObjectInputType::mouse_off);
                    msg.is_sent_by_system = true;
                                sendMessage(msg);
                            }

                        }
                    }

                }

            }
            else
            {
                // Then do the rest
                for (auto it = m_mouse_button_subscriptions[e.mouse_event].begin(); it != m_mouse_button_subscriptions[e.mouse_event].end(); ++it)
                {
                    // Check if HUD Object
                    if (it->second->is_screen_bound)
                    {
                        if (f_input.isInBoundary(static_mouse_pos, *it->second))
                        {
                            // Send message to object
                            InputMessage msg;
                            msg.object_id = it->first;
                            msg.type = IMessageType::input_triggered;
                            msg.object_input = ObjectInput(static_cast<ObjectInputType>(e.mouse_event));
                            msg.is_sent_by_system = true;
                            sendMessage(msg);
                        }
                    }
                    else
                    {
                        if (f_input.isInBoundary(camera_mouse_pos, *it->second))
                        {
                            // Send message to object
                            InputMessage msg;
                            msg.object_id = it->first;
                            msg.type = IMessageType::input_triggered;
                            msg.object_input = ObjectInput(static_cast<ObjectInputType>(e.mouse_event));
                            msg.is_sent_by_system = true;
                            sendMessage(msg);
                        }
                    }
                }
            }

            break;
        }
        case framework::InputEventType::key_down:
        {
            for (auto it = m_key_subscription[e.key].begin(); it != m_key_subscription[e.key].end(); ++it)
            {
                InputMessage msg;
                msg.object_id = *it;
                msg.type = IMessageType::input_triggered;
                msg.object_input = ObjectInput(ObjectInputType::key_down, e.key);
                    msg.is_sent_by_system = true;
                sendMessage(msg);
            }

            break;
        }
        case framework::InputEventType::key_up:
        {
            for (auto it = m_key_subscription[e.key].begin(); it != m_key_subscription[e.key].end(); ++it)
            {
                InputMessage msg;
                msg.object_id = *it;
                msg.type = IMessageType::input_triggered;
                msg.object_input = ObjectInput(ObjectInputType::key_up, e.key);
                    msg.is_sent_by_system = true;
                sendMessage(msg);
            }

            break;
        }
        default:;
        }
    }
}

void jinny::InputSystem::handleMessage(const InputMessage msg)
{
    switch (msg.type)
    {
    case IMessageType::subscribe_input:
        switch (msg.object_input.type)
        {
        case ObjectInputType::mouse_over:
            m_mouse_over_subscriptions[{msg.object_id, msg.object_shape}] = false;
            break;
        case ObjectInputType::left_mouse_press:
            if (m_mouse_button_subscriptions.find(framework::MouseEvent::left_down) != m_mouse_button_subscriptions.end())
            {
                m_mouse_button_subscriptions[framework::MouseEvent::left_down].push_back({ msg.object_id, msg.object_shape });
            }
            else
            {
                m_mouse_button_subscriptions[framework::MouseEvent::left_down] = { { msg.object_id, msg.object_shape } };
            }

            if (m_mouse_button_subscriptions.find(framework::MouseEvent::left_up) != m_mouse_button_subscriptions.end())
            {
                m_mouse_button_subscriptions[framework::MouseEvent::left_up].push_back({ msg.object_id, msg.object_shape });
            }
            else
            {
                m_mouse_button_subscriptions[framework::MouseEvent::left_up] = { { msg.object_id, msg.object_shape } };
            }

            break;
        case ObjectInputType::right_mouse_press:

            if (m_mouse_button_subscriptions.find(framework::MouseEvent::right_down) != m_mouse_button_subscriptions.end())
            {
                m_mouse_button_subscriptions[framework::MouseEvent::right_down].push_back({ msg.object_id, msg.object_shape });
            }
            else
            {
                m_mouse_button_subscriptions[framework::MouseEvent::right_down] = { { msg.object_id, msg.object_shape } };
            }

            if (m_mouse_button_subscriptions.find(framework::MouseEvent::right_up) != m_mouse_button_subscriptions.end())
            {
                m_mouse_button_subscriptions[framework::MouseEvent::right_up].push_back({ msg.object_id, msg.object_shape });
            }
            else
            {
                m_mouse_button_subscriptions[framework::MouseEvent::right_up] = { { msg.object_id, msg.object_shape } };
            }
            break;
        case ObjectInputType::key_press:

            if (m_key_subscription.find(msg.object_input.key) != m_key_subscription.end())
            {
                m_key_subscription[msg.object_input.key].push_back(msg.object_id);
            }
            else
            {
                m_key_subscription[msg.object_input.key] = { msg.object_id };
            }
            break;
        default: ;
        }

        break;
    default:;
    }
}

