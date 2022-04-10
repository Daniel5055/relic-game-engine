#include "PlayerInputComponent.h"

relic::PlayerInputComponent::PlayerInputComponent()
{
    // Subscribe to input
    subscribeInput(ObjectInputType::key_press, 'w');
    subscribeInput(ObjectInputType::key_press, 'a');
    subscribeInput(ObjectInputType::key_press, 's');
    subscribeInput(ObjectInputType::key_press, 'd');
}

void relic::PlayerInputComponent::handleMessage(const Message<InputObjectType>& msg)
{
    switch (msg.type)
    {
    case InputObjectType::input_triggered:
        auto o_i = std::any_cast<ObjectInput>(msg.value);

        if (o_i.type == ObjectInputType::key_down)
        {
            if (m_keys_down[o_i.key] == false)
            {
                m_keys_down[o_i.key] = true;

                const Message e{ ObjectType::input_triggered, std::make_any<ObjectInput>(o_i) };
                MessageSender<ObjectType>::sendMessage(e);
            }
        }
        else
        {
            m_keys_down[o_i.key] = false;

            const Message e{ ObjectType::input_triggered, std::make_any<ObjectInput>(o_i) };
            MessageSender<ObjectType>::sendMessage(e);
        }
        break;
    }
}
