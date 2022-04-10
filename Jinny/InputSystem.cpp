#include "InputSystem.h"

#include "Input.h"
#include "InputEvent.h"
#include "ObjectInput.h"

#include "Point.h"
#include "Window.h"

relic::InputSystem::InputSystem(const framework::Window& window, const framework::Input& input)
    :MessageReceiver<InputSystemType>(Identifier::null_identifier),
    MessageSender<InputObjectType>(Identifier::null_identifier),
    MessageSender<GameSystemType>(Identifier::null_identifier), f_input(input), f_window(window)
{
}

void relic::InputSystem::doUpdates()
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
            Message<GameSystemType> msg;
            msg.type = GameSystemType::exit_pressed;

            MessageSender<GameSystemType>::sendMessage(msg);

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
                            Message msg{ InputObjectType::input_triggered, ObjectInput(ObjectInputType::mouse_over) };
                            msg.to = &it->first.first;
                            MessageSender<InputObjectType>::sendMessage(msg);
                        }
                        else
                        {
                            // Check for mouse off
                            if (it->second == true)
                            {
                                it->second = false;

                                Message msg{ InputObjectType::input_triggered, ObjectInput(ObjectInputType::mouse_off) };
                                msg.to = &it->first.first;
                                MessageSender<InputObjectType>::sendMessage(msg);
                            }

                        }
                    }
                    else
                    {
                        if (f_input.isInBoundary(camera_mouse_pos, *it->first.second))
                        {
                            it->second = true;

                            // Send message to object
                            Message msg{ InputObjectType::input_triggered, ObjectInput(ObjectInputType::mouse_over) };
                            msg.to = &it->first.first;
                            MessageSender<InputObjectType>::sendMessage(msg);
                        }
                        else
                        {
                            // Check for mouse off
                            if (it->second == true)
                            {
                                it->second = false;

                                Message msg{ InputObjectType::input_triggered, ObjectInput(ObjectInputType::mouse_off) };
                                msg.to = &it->first.first;
                                MessageSender<InputObjectType>::sendMessage(msg);
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
                            Message msg{ InputObjectType::input_triggered, ObjectInput(static_cast<ObjectInputType>(e.mouse_event)) };
                            msg.to = &it->first;
                            MessageSender<InputObjectType>::sendMessage(msg);
                        }
                    }
                    else
                    {
                        if (f_input.isInBoundary(camera_mouse_pos, *it->second))
                        {
                            // Send message to object
                            Message msg{ InputObjectType::input_triggered, ObjectInput(static_cast<ObjectInputType>(e.mouse_event)) };
                            msg.to = &it->first;
                            MessageSender<InputObjectType>::sendMessage(msg);
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
                Message msg{ InputObjectType::input_triggered, ObjectInput(ObjectInputType::key_down, e.key) };
                msg.to = &*it;
                MessageSender<InputObjectType>::sendMessage(msg);
            }

            break;
        }
        case framework::InputEventType::key_up:
        {
            for (auto it = m_key_subscription[e.key].begin(); it != m_key_subscription[e.key].end(); ++it)
            {
                Message msg{ InputObjectType::input_triggered, ObjectInput(ObjectInputType::key_up, e.key) };
                msg.to = &*it;
                MessageSender<InputObjectType>::sendMessage(msg);
            }

            break;
        }
        default:;
        }
    }
}

void relic::InputSystem::handleMessage(Message<InputSystemType> msg)
{
    switch (msg.type)
    {
    case InputSystemType::subscribe_input:
    {

        const auto o_i = std::any_cast<ObjectInput>(msg.value);
        switch (o_i.type)
        {
        case ObjectInputType::mouse_over:
            m_mouse_over_subscriptions[{*msg.from, o_i.mouse_shape}] = false;
            break;
        case ObjectInputType::left_mouse_press:
            if (m_mouse_button_subscriptions.find(framework::MouseEvent::left_down) != m_mouse_button_subscriptions.end())
            {
                m_mouse_button_subscriptions[framework::MouseEvent::left_down].push_back({ *msg.from, o_i.mouse_shape });
            }
            else
            {
                m_mouse_button_subscriptions[framework::MouseEvent::left_down] = { {*msg.from, o_i.mouse_shape} };
            }

            if (m_mouse_button_subscriptions.find(framework::MouseEvent::left_up) != m_mouse_button_subscriptions.end())
            {
                m_mouse_button_subscriptions[framework::MouseEvent::left_up].push_back({ *msg.from, o_i.mouse_shape });
            }
            else
            {
                m_mouse_button_subscriptions[framework::MouseEvent::left_up] = { {*msg.from, o_i.mouse_shape} };
            }

            break;
        case ObjectInputType::right_mouse_press:

            if (m_mouse_button_subscriptions.find(framework::MouseEvent::right_down) != m_mouse_button_subscriptions.end())
            {
                m_mouse_button_subscriptions[framework::MouseEvent::right_down].push_back({ *msg.from, o_i.mouse_shape });
            }
            else
            {
                m_mouse_button_subscriptions[framework::MouseEvent::right_down] = { {*msg.from, o_i.mouse_shape} };
            }

            if (m_mouse_button_subscriptions.find(framework::MouseEvent::right_up) != m_mouse_button_subscriptions.end())
            {
                m_mouse_button_subscriptions[framework::MouseEvent::right_up].push_back({ *msg.from, o_i.mouse_shape });
            }
            else
            {
                m_mouse_button_subscriptions[framework::MouseEvent::right_up] = { {*msg.from, o_i.mouse_shape} };
            }
            break;
        case ObjectInputType::key_press:

            if (m_key_subscription.find(o_i.key) != m_key_subscription.end())
            {
                m_key_subscription[o_i.key].push_back(*msg.from);
            }
            else
            {
                m_key_subscription[o_i.key] = { *msg.from };
            }
            break;
        default:;
        }

        break;
    }
    default:;
    }
}

