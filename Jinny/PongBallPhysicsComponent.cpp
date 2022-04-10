#include "PongBallPhysicsComponent.h"

relic::pong::PongBallPhysicsComponent::PongBallPhysicsComponent(const framework::Shape shape, Identifier
    left_wall_id,
    Identifier right_wall_id)
    :RigidBodyPhysicsComponent(10, 0, shape, framework::Material::pong_ball, 10, 10, { 1000, 0 })
    , MessageReceiver<PhysicsObjectType>(getObjectId()), MessageSender<PongType>(getObjectId())
    , m_left_wall_id(std::move(left_wall_id))
    , m_right_wall_id(std::move(right_wall_id))
{
    Message<PhysicsSystemType> msg;
    msg.type = PhysicsSystemType::register_collision_checking;
    MessageSender<PhysicsSystemType>::sendMessage(msg);
}

void relic::pong::PongBallPhysicsComponent::doUpdates()
{
    RigidBodyPhysicsComponent::doUpdates();
    handleMessages();
}

void relic::pong::PongBallPhysicsComponent::handleMessage(const Message<PhysicsObjectType> msg)
{
    switch (msg.type)
    {
    case PhysicsObjectType::collision_occurred:
        const auto colliding_id = std::any_cast<Identifier>(msg.value);
        if (colliding_id == m_left_wall_id)
        {
            MessageSender<PongType>::sendMessage({ PongType::right_win });
        }
        else if (colliding_id == m_right_wall_id)
        {
            MessageSender<PongType>::sendMessage({ PongType::left_win });
        }
        break;
    }
}

