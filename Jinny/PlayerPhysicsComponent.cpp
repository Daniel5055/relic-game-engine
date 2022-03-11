#include "PlayerPhysicsComponent.h"

#include "PhysicsData.h"
#include "RigidBody.h"

Jinny::PlayerPhysicsComponent::PlayerPhysicsComponent(double mass, double max_x_speed, double max_y_speed)
{
	m_rigid_body = nullptr;

	// Create Data
	m_data = new Framework::RigidBody(mass, 1000);

	m_data->doesHaveRigidBody();

	m_data->applyMFForce({ 0, -300});

}

void Jinny::PlayerPhysicsComponent::initialize(GameObject& object)
{
	setObject(&object);

	// Set Shape
	ObjectEvent o_event = *object.getQueueIterator();
	if (o_event.type == EventType::OBJECT_INITIALIZATION_SHAPE)
	{
		m_rigid_body = new Framework::RigidBody(o_event.shape, false, Framework::Material::ENTITY);
	}

	PhysicsMessage msg_1;
	msg_1.type = PMessageType::SET_RIGID_BODY;
	msg_1.object_ID = object.getObjectID();

	msg_1.rigid_body = m_rigid_body;

	pushMessage(msg_1);

	PhysicsMessage msg_2;
	msg_2.type = PMessageType::SET_PHYSICS_DATA;
	msg_2.object_ID = object.getObjectID();

	msg_2.data = m_data;

	pushMessage(msg_2);

}

void Jinny::PlayerPhysicsComponent::update()
{
	handleEvents();
	handleMessages();

	m_rigid_body->move(m_data->getTickMovement());
}

Jinny::PlayerPhysicsComponent::~PlayerPhysicsComponent()
{
	delete m_data;
	m_data = nullptr;

	delete m_rigid_body;
	m_rigid_body = nullptr;
}

void Jinny::PlayerPhysicsComponent::handleEvents()
{
	for (auto it = getObject()->getQueueIterator(); it != getObject()->getQueueEnd(); it++)
	{

		if (it->type == EventType::INPUT_TRIGGERED)
		{
			double is_down = 0;
			if (it->input.type == ObjectInputType::KEY_DOWN)
			{
				is_down = 1;
					
			}
			else if (it->input.type == ObjectInputType::KEY_UP)
			{
				is_down = -1;
			}

			switch (it->input.key)
			{
			case 'a':
				m_data->applyMFForce({ is_down * -500, 0 });

				break;

			case 'd':
				m_data->applyMFForce({ is_down * 500, 0 });

				break;

			case 'w':
				m_data->applyMFForce({ 0, is_down * -500 });

				break;

			case 's':
				m_data->applyMFForce({ 0, is_down * 500 });

				break;
			}
		}
	}
}

void Jinny::PlayerPhysicsComponent::handleMessages()
{

}
