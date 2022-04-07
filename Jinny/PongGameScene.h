#pragma once

#include "Scene.h"

namespace relic
{
    namespace pong
    {
        class PongGameScene final : public Scene
        {
            void doInitialisation() override;
        };
    }
}