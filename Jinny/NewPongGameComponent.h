#pragma once

#include "Component.h"
#include "Scene.h"
#include "MessageReceiver.h"
#include "MessageSender.h"
#include "PongType.h"
#include "GameType.h"

namespace relic::pong
{
    class NewPongGameComponent final
        : public Component
        , public MessageReceiver<PongType>
        , public MessageSender<GameSystemType>
    {
    public:
        explicit NewPongGameComponent(Scene* new_pong_game_scene);

    protected:
        void doUpdates() override;

    private:
        void handleMessage(Message<PongType> msg) override;
        
        Scene* m_new_scene{nullptr};
    };
}
