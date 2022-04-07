#include "PongPaddleInputComponent.h"

relic::pong::PongPaddleInputComponent::PongPaddleInputComponent(const char up_key, const char down_key)
{
    subscribeInput(ObjectInputType::key_press, up_key);
    subscribeInput(ObjectInputType::key_press, down_key);
    m_keys_down[up_key] = false;
    m_keys_down[down_key] = false;
}

void relic::pong::PongPaddleInputComponent::handleMessage(const InputMessage msg)
{
    switch (msg.type)
    {
    case IMessageType::input_triggered:
        if (msg.object_input.type == ObjectInputType::key_down)
        {
            if (!m_keys_down[msg.object_input.key])
            {
                m_keys_down[msg.object_input.key] = true;
                const ObjectEvent e{ ObjectEvent::Type::input_triggered, {msg.object_input} };
                sendEvent(e);
            }
        }
        else
        {
            m_keys_down[msg.object_input.key] = false;
            const ObjectEvent e{ ObjectEvent::Type::input_triggered, {msg.object_input} };
            sendEvent(e);
        }
    }
}
