#include "StaticRigidBodyPhysicsComponent.h"

#include "RigidBody.h"

jinny::StaticRigidBodyPhysicsComponent::StaticRigidBodyPhysicsComponent(const framework::Shape shape,
    const framework::Material material)
    :m_rigid_body(1, 0, { 0, 0 }, shape, material)
{
    m_rigid_body.setStatic(true);
    PhysicsMessage msg;
    msg.type = PMessageType::set_rigid_body;
    msg.object_id = getObjectId();
    msg.rigid_body = &m_rigid_body;

    sendMessage(msg);

}
