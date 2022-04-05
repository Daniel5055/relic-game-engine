#include "MouseInputComponent.h"

relic::MouseInputComponent::MouseInputComponent(const framework::Shape mouse_area)
    :m_mouse_area(mouse_area)
{
    // subscribe to mouse hovering and pressing in mouse area
    InputMessage msg;
    msg.type = IMessageType::subscribe_input;
    msg.object_id = getObjectId();
    msg.object_shape = &m_mouse_area;
    msg.object_input.type = ObjectInputType::left_mouse_press;
    sendMessage(msg);

    // Object Input 2
    msg.object_input.type = ObjectInputType::mouse_over;
    sendMessage(msg);
}

void relic::MouseInputComponent::handleMessage(const InputMessage msg)
{
    switch (msg.type)
    {
    case IMessageType::input_triggered:

        const ObjectEvent e{ObjectEvent::Type::input_triggered, {ObjectInput(msg.object_input.type)}};

        // Mouse Clicking
        switch(msg.object_input.type)
        {
        case ObjectInputType::left_mouse_down:
            m_mouse_button_down = false;
            break;
        case ObjectInputType::left_mouse_up:
            m_mouse_button_down = false;
            break;
        case ObjectInputType::mouse_off: 
            m_mouse_button_down = false;
            break;
        }
        // Send the event
        sendEvent(e);

        break;
    }
}

void relic::MouseInputComponent::handleEvent(ObjectEvent e)
{
    switch (e.type)
    {
    case ObjectEvent::Type::move:
        m_mouse_area.x += e.movement.x;
        m_mouse_area.y += e.movement.y;
        break;
    default:;
    }
}

void relic::MouseInputComponent::doUpdates()
{
    // Have to manually call to handleMessages
    MessageReceiver<InputMessage>::handleMessages();
}

