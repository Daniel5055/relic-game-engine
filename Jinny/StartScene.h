#pragma once

#include "Scene.h"

namespace relic
{
    class StartScene final : public Scene
    {
        void doInitialisation() override;
    };
}
