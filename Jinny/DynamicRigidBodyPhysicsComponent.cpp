#include "DynamicRigidBodyPhysicsComponent.h"

#include "RigidBody.h"

Jinny::DynamicRigidBodyPhysicsComponent::DynamicRigidBodyPhysicsComponent(double mass, double max_x_speed, double max_y_speed, Framework::Material material, Framework::Vector force)
{
	m_data = nullptr;
	m_rigid_body = nullptr;

	
	// Create Data
	m_data = new Framework::RigidBody(mass, 200);

	m_data->applySFForce(force);

	m_material = material;

	m_data->applyMFForce({ 0, -60});
}

void Jinny::DynamicRigidBodyPhysicsComponent::initialize(GameObject& object)
{
	setObject(&object);

	// Set Shape
	ObjectEvent o_event = *object.getQueueIterator();
	if (o_event.type == EventType::OBJECT_INITIALIZATION_SHAPE)
	{

		m_rigid_body = new Framework::RigidBody(o_event.shape, false, m_material);

		PhysicsMessage msg_2;
		msg_2.type = PMessageType::SET_PHYSICS_DATA;
		msg_2.object_ID = object.getObjectID();

		msg_2.data = m_data;

		pushMessage(msg_2);

		PhysicsMessage msg;
		msg.type = PMessageType::SET_RIGID_BODY;
		msg.object_ID = object.getObjectID();
		msg.rigid_body = m_rigid_body;

		pushMessage(msg);



	}
}

void Jinny::DynamicRigidBodyPhysicsComponent::update()
{
	m_rigid_body->move(m_data->getTickMovement());
}

Jinny::DynamicRigidBodyPhysicsComponent::~DynamicRigidBodyPhysicsComponent()
{
	delete m_rigid_body;
	m_rigid_body = nullptr;

	delete m_data;
	m_data = nullptr;
}