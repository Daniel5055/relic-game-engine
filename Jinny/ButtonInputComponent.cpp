#include "ButtonInputComponent.h"

#include "Point.h"

relic::ButtonInputComponent::ButtonInputComponent(const framework::Shape mouse_area)
    : MessageReceiver<ObjectType>(getId(), true), MessageSender<ButtonType>(getId(), true), m_mouse_area(mouse_area)
{
    // subscribe to mouse hovering and pressing in mouse area
    subscribeInput(ObjectInputType::left_mouse_press, &m_mouse_area);
    subscribeInput(ObjectInputType::mouse_over, &m_mouse_area);
}

void relic::ButtonInputComponent::handleMessage(const Message<InputObjectType>& msg)
{
    switch (msg.type)
    {
    case InputObjectType::input_triggered:

        // Mouse Clicking
        switch (std::any_cast<ObjectInput>(msg.value).type)
        {
        case ObjectInputType::left_mouse_down:
            m_mouse_button_down = true;
            MessageSender<ButtonType>::sendImmediateMessage({ ButtonType::button_down });
            break;

        case ObjectInputType::left_mouse_up:
            if (m_mouse_button_down)
            {
                m_mouse_button_down = false;

                MessageSender<ButtonType>::sendImmediateMessage({ ButtonType::button_pressed });
            }
            //MessageSender<ButtonType>::sendMessage({ButtonType::button_focused});
            break;
        case ObjectInputType::mouse_off:
            m_mouse_button_down = false;
            MessageSender<ButtonType>::sendImmediateMessage({ ButtonType::button_unfocused });
            break;
        case ObjectInputType::mouse_over:
            if (!m_mouse_button_down)
            {
                MessageSender<ButtonType>::sendImmediateMessage({ ButtonType::button_focused });
            }
            break;
        }

        break;
    }
}

void relic::ButtonInputComponent::handleMessage(const Message<ObjectType>& msg)
{
    switch (msg.type)
    {
    case ObjectType::move:
    {
        const framework::Point movement = std::any_cast<framework::Point>(msg.value);
        m_mouse_area.x += movement.x;
        m_mouse_area.y += movement.y;
        break;
    }
    default:;
    }
}

void relic::ButtonInputComponent::doUpdates()
{
    InputComponent::doUpdates();
    MessageReceiver<ObjectType>::handleMessages();
}

