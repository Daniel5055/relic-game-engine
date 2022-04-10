#include "MouseInputComponent.h"

#include "Point.h"

relic::MouseInputComponent::MouseInputComponent(const framework::Shape mouse_area)
    : MessageReceiver<ObjectType>(getObjectId(), true), m_mouse_area(mouse_area)
{
    // subscribe to mouse hovering and pressing in mouse area
    subscribeInput(ObjectInputType::left_mouse_press, &m_mouse_area);
    subscribeInput(ObjectInputType::mouse_over, &m_mouse_area);
}

void relic::MouseInputComponent::handleMessage(const Message<InputObjectType>& msg)
{
    switch (msg.type)
    {
    case InputObjectType::input_triggered:

        Message e{ ObjectType::input_triggered, msg.value };

        // Mouse Clicking
        switch (std::any_cast<ObjectInput>(msg.value).type)
        {
        case ObjectInputType::left_mouse_down:
            m_mouse_button_down = false;
            MessageSender<ObjectType>::sendMessage(e);
            break;

        case ObjectInputType::left_mouse_up:
            if (m_mouse_button_down)
            {
                m_mouse_button_down = false;

                MessageSender<ObjectType>::sendMessage(e);
            }
            break;
        case ObjectInputType::mouse_off:
            m_mouse_button_down = false;
            MessageSender<ObjectType>::sendMessage(e);
            break;
        case ObjectInputType::mouse_over:
            MessageSender<ObjectType>::sendMessage(e);
            break;
        }

        break;
    }
}

void relic::MouseInputComponent::handleMessage(const Message<ObjectType>& msg)
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

void relic::MouseInputComponent::doUpdates()
{
    InputComponent::doUpdates();

    // Have to handles the new receivers messages
    MessageReceiver<ObjectType>::handleMessages();
}

