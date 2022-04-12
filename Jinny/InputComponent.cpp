#include "InputComponent.h"

relic::InputComponent::InputComponent()
    : MessageReceiver<InputObjectType>(getId())
    , MessageSender<InputSystemType>(getId())
    , MessageSender<ObjectType>(getId(), true)
{
}

void relic::InputComponent::subscribeInput(ObjectInputType type, char key)
{
    // Subscribe to player movement keys
    Message<InputSystemType> msg;
    msg.type = InputSystemType::subscribe_input;
    msg.value = std::make_any<ObjectInput>(type, key);
    MessageSender<InputSystemType>::sendMessage(std::move(msg));
}

void relic::InputComponent::subscribeInput(ObjectInputType type, framework::Shape* mouse_area)
{
    // Subscribe to player movement keys
    Message<InputSystemType> msg;
    msg.type = InputSystemType::subscribe_input;
    ObjectInput o_i{ type };
    
    o_i.mouse_shape = mouse_area;
    msg.value = std::make_any<ObjectInput>(o_i);
    MessageSender<InputSystemType>::sendMessage(std::move(msg));
}

void relic::InputComponent::doUpdates()
{
    // Handling incoming messages from input system
    handleMessages();
}

