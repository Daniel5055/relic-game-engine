#include "PlayerPhysicsComponent.h"

# include "Material.h"
#include "ObjectInput.h"
#include "RigidBody.h"

relic::PlayerPhysicsComponent::PlayerPhysicsComponent(const double mass, const double max_x_speed, const double max_y_speed, const framework::Shape shape)
    : RigidBodyPhysicsComponent(mass, 0, shape, framework::Material::entity, max_x_speed, max_y_speed)
    , MessageReceiver<ObjectType>(getObjectId(), true)
{
}

void relic::PlayerPhysicsComponent::handleMessage(const Message<ObjectType>& msg)
{
    if (msg.type == ObjectType::input_triggered)
    {
        const auto o_i = std::any_cast<ObjectInput>(msg.value);
        double is_down = 0;
        if (o_i.type == ObjectInputType::key_down)
        {
            is_down = 1;

        }
        else if (o_i.type == ObjectInputType::key_up)
        {
            is_down = -1;
        }

        // TODO: Change this so that Player physics does not have to care about the key, but rather care on the idea, (Like move north south etc)
        switch (o_i.key)
        {
        case 'a':
            getRigidBody().applyMFForce({ is_down * -100, 0 });
            break;

        case 'd':
            getRigidBody().applyMFForce({ is_down * 100, 0 });
            break;

        case 'w':
            getRigidBody().applyMFForce({ 0, is_down * -100 });
            break;

        case 's':
            getRigidBody().applyMFForce({ 0, is_down * 100 });
            break;
        }
    }
}

void relic::PlayerPhysicsComponent::doUpdates()
{
    handleMessages();
    RigidBodyPhysicsComponent::doUpdates();
}
