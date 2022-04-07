#include "InputComponent.h"

void relic::InputComponent::subscribeInput(ObjectInputType type, char key)
{
    // Subscribe to player movement keys
    InputMessage msg;
    msg.type = IMessageType::subscribe_input;
    msg.object_id = getObjectId();
    msg.object_input = {type, key};
    sendMessage(msg);
}

void relic::InputComponent::doUpdates()
{
    MessageReceiver<InputMessage>::handleMessages();
}

void relic::InputComponent::prepareMessage(InputMessage& msg)
{
    if (msg.object_id == k_unset_id)
    {
        msg.object_id = getObjectId();
    }
}
