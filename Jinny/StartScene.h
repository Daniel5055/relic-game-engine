#pragma once

#include "Scene.h"

namespace jinny
{
    class StartScene : public Scene
    {
    private:
        void doInitialisation() override;
    };
}
