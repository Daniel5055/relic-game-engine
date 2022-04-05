#pragma once

#include "Scene.h"

namespace relic
{
    class StartScene : public Scene
    {
    private:
        void doInitialisation() override;
    };
}
