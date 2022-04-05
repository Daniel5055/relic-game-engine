#pragma once

#include "CoreComponent.h"

namespace framework
{
    struct Shape;
}

namespace relic
{
    /**
     * \brief Component used to change the camera of a scene
     */
    class CameraCoreComponent final : public CoreComponent
    {
    public:
        explicit CameraCoreComponent(framework::Shape* new_camera_shape);
    };
}