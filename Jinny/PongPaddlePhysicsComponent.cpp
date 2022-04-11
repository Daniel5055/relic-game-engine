#include "PongPaddlePhysicsComponent.h"

#include "ObjectInput.h"

relic::pong::PongPaddlePhysicsComponent::PongPaddlePhysicsComponent(const framework::Shape shape, const framework::Direction facing,
                                                                    const char up_key, const char down_key)
    :RigidBodyPhysicsComponent(10, 2000, shape, framework::Material::entity), MessageReceiver<ObjectType>(getObjectId(), true), m_up_key(up_key), m_down_key(down_key)
{
    getRigidBody().setStatic(true);
    getRigidBody().setSideSolidity(framework::Direction::north, false);
    getRigidBody().setSideSolidity(framework::Direction::south, false);
    getRigidBody().setSideSolidity(framework::Direction::west, false);
    getRigidBody().setSideSolidity(framework::Direction::east, false);
    getRigidBody().setSideSolidity(facing, true);
}

void relic::pong::PongPaddlePhysicsComponent::doUpdates()
{
    RigidBodyPhysicsComponent::doUpdates();
    handleMessages();
}

void relic::pong::PongPaddlePhysicsComponent::handleMessage(const Message<ObjectType>& msg)
{
    switch (msg.type)
    {
    case ObjectType::input_triggered:
        double is_down = 0;
        const auto o_i = std::any_cast<ObjectInput>(msg.value);

        if (o_i.type == ObjectInputType::key_down)
        {
            is_down = 1;
        }
        else if (o_i.type == ObjectInputType::key_up)
        {
            is_down = -1;
        }

        if (o_i.key == m_up_key)
        {
            getRigidBody().applyMFForce({ 0, is_down * -1000 });
        }
        else if (o_i.key == m_down_key)
        {
            getRigidBody().applyMFForce({ 0, is_down * 1000 });
        }

        break;
    }
}
