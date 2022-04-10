#pragma once

#include "Component.h"

#include "MessageReceiver.h"
#include "MessageSender.h"

#include "GameType.h"

namespace framework
{
    struct Shape;
}

namespace relic
{
    /**
     * \brief Component used to change the camera of a scene
     */
    class CameraCoreComponent final
    : public Component
    , public MessageSender<GameSystemType>
    {
    public:
        explicit CameraCoreComponent(framework::Shape* new_camera_shape);
    };
}