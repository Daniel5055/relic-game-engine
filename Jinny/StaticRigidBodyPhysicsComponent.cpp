#include "StaticRigidBodyPhysicsComponent.h"

#include "RigidBody.h"

Jinny::StaticRigidBodyPhysicsComponent::StaticRigidBodyPhysicsComponent(Framework::Material material)
{
	m_rigid_body = nullptr;
	m_material = material;
}

void Jinny::StaticRigidBodyPhysicsComponent::initialize(GameObject& object)
{
	setObject(&object);

	// Set Shape
	ObjectEvent o_event = *object.getQueueIterator();
	if (o_event.type == EventType::OBJECT_INITIALIZATION_SHAPE)
	{
		m_rigid_body->setShape(o_event.shape);
		m_rigid_body->setStatic(true);

		PhysicsMessage msg;
		msg.type = PMessageType::SET_RIGID_BODY;
		msg.object_ID = object.getObjectID();
		msg.rigid_body = m_rigid_body;

		pushMessage(msg);
		
	}
}

Jinny::StaticRigidBodyPhysicsComponent::~StaticRigidBodyPhysicsComponent()
{
	delete m_rigid_body;
	m_rigid_body = nullptr;
}
