#include "CameraCoreComponent.h"

#include "Shape.h"

jinny::CameraCoreComponent::CameraCoreComponent(framework::Shape* new_camera_shape)
{
    // Sends a message to the game to change the camera
    GameMessage msg;
    msg.type = GameMessageType::set_camera;
    msg.shape_ptr = new_camera_shape;

    sendMessage(msg);
}
