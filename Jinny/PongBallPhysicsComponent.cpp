#include "PongBallPhysicsComponent.h"

relic::pong::PongBallPhysicsComponent::PongBallPhysicsComponent(const framework::Shape shape, const int left_wall_id, const int right_wall_id)
    :RigidBodyPhysicsComponent(10, 0, shape, framework::Material::pong_ball, 10, 10, { 1000, 0 }),
    m_left_wall_id(left_wall_id), m_right_wall_id(right_wall_id)
{
    PhysicsMessage msg;
    msg.type = PMessageType::register_collision_checking;
    msg.object_id = getObjectId();
    sendMessage(msg);
}

void relic::pong::PongBallPhysicsComponent::handleMessage(const PhysicsMessage msg)
{
    switch (msg.type)
    {
    case PMessageType::collision_occurred:
        if (msg.colliding_object_id == m_left_wall_id)
        {
            int x = 0;
        }
        else if (msg.colliding_object_id == m_right_wall_id)
        {
            int x = 0;
        }
        break;
    }
}

