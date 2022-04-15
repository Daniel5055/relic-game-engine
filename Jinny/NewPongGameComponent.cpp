#include "NewPongGameComponent.h"

relic::pong::NewPongGameComponent::NewPongGameComponent(Scene* new_pong_game_scene)
    :MessageReceiver(getId()), MessageSender<GameSystemType>(getId()), m_new_scene(new_pong_game_scene)
{
}

void relic::pong::NewPongGameComponent::doUpdates()
{
    Component::doUpdates();
    handleMessages();
}

void relic::pong::NewPongGameComponent::handleMessage(const Message<PongType>& msg)
{
    if (msg.type == PongType::left_win || msg.type == PongType::right_win)
    {
        MessageSender<GameSystemType>::sendMessage({ GameSystemType::change_scene, std::make_any<Scene*>(m_new_scene) });
    }
}
