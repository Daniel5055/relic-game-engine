#include "PongPaddleInputComponent.h"

relic::pong::PongPaddleInputComponent::PongPaddleInputComponent(const char up_key, const char down_key)
{
    subscribeInput(ObjectInputType::key_press, up_key);
    subscribeInput(ObjectInputType::key_press, down_key);
    m_keys_down[up_key] = false;
    m_keys_down[down_key] = false;
}

void relic::pong::PongPaddleInputComponent::handleMessage(const Message<InputObjectType>& msg)
{
    switch (msg.type)
    {
    case InputObjectType::input_triggered:
        const auto o_i = std::any_cast<ObjectInput>(msg.value);

        if (o_i.type == ObjectInputType::key_down)
        {
            if (!m_keys_down[o_i.key])
            {
                m_keys_down[o_i.key] = true;
                const Message e{ ObjectType::input_triggered, std::make_any<ObjectInput>(o_i) };
                MessageSender<ObjectType>::sendMessage(e);
            }
        }
        else
        {
            if (m_keys_down[o_i.key])
            {
                m_keys_down[o_i.key] = false;
                const Message e{ ObjectType::input_triggered, std::make_any<ObjectInput>(o_i) };
                MessageSender<ObjectType>::sendMessage(e);
            }
        }
    }
}
