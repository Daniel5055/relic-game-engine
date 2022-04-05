#include "SceneChangeCoreComponent.h"

relic::SceneChangeCoreComponent::SceneChangeCoreComponent(const ObjectInput trigger_input, Scene* new_scene)
    :m_next_scene(new_scene), m_trigger_input(trigger_input)
{
}

void relic::SceneChangeCoreComponent::handleEvent(const ObjectEvent e)
{
    switch (e.type)
    {
    case ObjectEvent::Type::input_triggered:

        // Check if required input
        if (e.input.type == m_trigger_input.type && e.input.key == m_trigger_input.key)
        {
            // Send message to game to change scene
            GameMessage game_msg;
            game_msg.type = GameMessageType::change_scene;
            game_msg.scene_ptr = m_next_scene;

            sendMessage(game_msg);
        }
        break;
    }
}
