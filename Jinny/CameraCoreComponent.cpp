#include "CameraCoreComponent.h"

#include "Shape.h"

relic::CameraCoreComponent::CameraCoreComponent(framework::Shape* new_camera_shape)
    :MessageSender(getObjectId())
{
    // Sends a message to the game to change the camera
    const Message msg{ GameSystemType::set_camera, std::make_any<framework::Shape*>(new_camera_shape) };
    sendMessage(msg);
}
