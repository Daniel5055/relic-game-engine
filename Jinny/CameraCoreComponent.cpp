#include "CameraCoreComponent.h"

#include "Shape.h"
#include "Point.h"

void Jinny::CameraCoreComponent::initialize(GameObject& object)
{
    setObject(&object);

    auto event_ptr = object.getQueueIterator();

    GameMessage msg;
    msg.type = GameMessageType::SET_CAMERA;
    msg.shape_ptr = event_ptr->shape;

    pushMessage(msg);


}
