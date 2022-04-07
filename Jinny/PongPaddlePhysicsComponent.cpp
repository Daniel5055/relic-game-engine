#include "PongPaddlePhysicsComponent.h"

relic::pong::PongPaddlePhysicsComponent::PongPaddlePhysicsComponent(const framework::Shape shape, const char up_key, const char down_key)
    :RigidBodyPhysicsComponent(10, 2000, shape, framework::Material::entity), m_up_key(up_key), m_down_key(down_key)
{
    getRigidBody().setStatic(true);
}

void relic::pong::PongPaddlePhysicsComponent::handleEvent(const ObjectEvent e)
{
    switch (e.type)
    {
    case ObjectEvent::Type::input_triggered:
        double is_down = 0;

        if (e.input.type == ObjectInputType::key_down)
        {
            is_down = 1;
        }
        else if (e.input.type == ObjectInputType::key_up)
        {
            is_down = -1;
        }

        if (e.input.key == m_up_key)
        {
            getRigidBody().applyMFForce({ 0, is_down * -1000 });
        }
        else if (e.input.key == m_down_key)
        {
            getRigidBody().applyMFForce({ 0, is_down * 1000 });
        }

        break;
    }
}
