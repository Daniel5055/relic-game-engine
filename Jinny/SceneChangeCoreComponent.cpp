#include "SceneChangeCoreComponent.h"

relic::SceneChangeCoreComponent::SceneChangeCoreComponent(const ObjectInput trigger_input, Scene* new_scene)
    : MessageReceiver(getId(), true), MessageSender(getId()), m_next_scene(new_scene),
      m_trigger_input(trigger_input)
{
}

void relic::SceneChangeCoreComponent::handleMessage(const relic::Message<ObjectType>& msg)
{
    switch (msg.type)
    {
    case ObjectType::input_triggered:

        // Check if required input
        const auto o_i = std::any_cast<ObjectInput>(msg.value);
        if (o_i.type == m_trigger_input.type && o_i.key == m_trigger_input.key)
        {
            // Send message to game to change scene
            const Message m{ GameSystemType::change_scene, std::make_any<Scene*>(m_next_scene) };
            sendMessage(m);
        }
        break;
    }
}
