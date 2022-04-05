#include "PlayerInputComponent.h"

relic::PlayerInputComponent::PlayerInputComponent()
{
    // Subscribe to player movement keys
    InputMessage msg;
    msg.type = IMessageType::subscribe_input;
    msg.object_id = getObjectId();
    msg.object_input = {ObjectInputType::key_press, 'a'};

    m_keys_down['a'] = false;
    sendMessage(msg);

    msg.object_input.key = 'd';
    m_keys_down['d'] = false;
    sendMessage(msg);

    msg.object_input.key = 'w';
    m_keys_down['w'] = false;
    sendMessage(msg);

    msg.object_input.key = 's';
    m_keys_down['s'] = false;
    sendMessage(msg);
}

void relic::PlayerInputComponent::doUpdates()
{
    MessageReceiver<InputMessage>::handleMessages();
}

void relic::PlayerInputComponent::handleMessage(const InputMessage msg)
{
    switch (msg.type)
    {
    case IMessageType::input_triggered:
        if (msg.object_input.type == ObjectInputType::key_down)
        {
            if (m_keys_down[msg.object_input.key] == false)
            {
                m_keys_down[msg.object_input.key] = true;

                const ObjectEvent e = {ObjectEvent::Type::input_triggered, {msg.object_input}};
                sendEvent(e);
            }
        }
        else
        {
            m_keys_down[msg.object_input.key] = false;

            const ObjectEvent e = {ObjectEvent::Type::input_triggered, {msg.object_input}};
            sendEvent(e);
        }
        break;
    }
}
