#pragma once

#include "MessageReceiver.h"
#include "GameMessage.h"
#include "InputMessage.h"
#include "PhysicsMessage.h"
#include "GraphicsMessage.h"

namespace relic
{
    /**
     * \brief Base abstract class of game used for receiving messages, used to hide implementation
     */
    class MultiMessageReceiver
        : public MessageReceiver<GameMessage>
        , public MessageReceiver<InputMessage>
        , public MessageReceiver<PhysicsMessage>
        , public MessageReceiver<GraphicsMessage>
    {
    protected:
        ~MultiMessageReceiver() = default;
    private:
        void handleMessage(GameMessage msg) override = 0;
        void handleMessage(InputMessage msg) override = 0;
        void handleMessage(PhysicsMessage msg) override = 0;
        void handleMessage(GraphicsMessage msg) override = 0;
    };
}

