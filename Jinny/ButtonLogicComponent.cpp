#include "ButtonLogicComponent.h"

relic::ButtonLogicComponent::ButtonLogicComponent()
    :MessageReceiver<ButtonType>(getId(), true), MessageSender<GraphicsObjectType>(getId(), true)
{

}

void relic::ButtonLogicComponent::doUpdates()
{
    Component::doUpdates();
    MessageReceiver<ButtonType>::handleMessages();
}

void relic::ButtonLogicComponent::handleMessage(const Message<ButtonType>& msg)
{
    switch (msg.type)
    {
    case ButtonType::button_down:
        MessageSender<GraphicsObjectType>::sendImmediateMessage({
            GraphicsObjectType::change_clip, std::make_any<int>(static_cast<int>(ButtonState::button_down))
            });
        break;
    case ButtonType::button_pressed:
        MessageSender<GraphicsObjectType>::sendImmediateMessage({
            GraphicsObjectType::change_clip, std::make_any<int>(static_cast<int>(ButtonState::button_focused))
            });

        onPress();
        break;
    case ButtonType::button_focused:
        MessageSender<GraphicsObjectType>::sendImmediateMessage({
            GraphicsObjectType::change_clip, std::make_any<int>(static_cast<int>(ButtonState::button_focused))
            });
        break;
    case ButtonType::button_unfocused:
        MessageSender<GraphicsObjectType>::sendImmediateMessage({
            GraphicsObjectType::change_clip, std::make_any<int>(static_cast<int>(ButtonState::button_neutral))
            });
        break;
    }
}
