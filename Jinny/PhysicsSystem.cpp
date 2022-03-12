#include "PhysicsSystem.h"

#include "Physics.h"

#include "RigidBody.h"
#include "Shape.h"

Jinny::PhysicsSystem::PhysicsSystem()
{
	m_acceleration_due_to_gravity = 0;
}

void Jinny::PhysicsSystem::intialize(Framework::Physics* physics, MessageBoard<PhysicsMessage>* message_board)
{
	m_message_board = message_board;

	f_physics = physics;

	m_col_manager = new GridCollisionManager(physics, m_rigid_bodies);
	m_col_manager->initialize();

}

void Jinny::PhysicsSystem::update()
{
	// Handle Messages
	handleMessages();

	// Check for friction
	checkFriction();

	// I think there is clash between dampening and friction
	checkDampening();

	m_col_manager->updateCollisions();

	// Iterate through object and reset time after tick
	for (auto it = m_rigid_bodies.begin(); it != m_rigid_bodies.end(); it++)
	{
		// Used to be f_physics->nextStep(it->second)?
		it->second->setTimeAfterTick(0);
	}

}

void Jinny::PhysicsSystem::close()
{
}

void Jinny::PhysicsSystem::handleMessages()
{
	// NOTE: for simplicity, physics based objects cannot be static

	int size = m_message_board->getQueueSize();
	for (int it = 0; it < size; it++)
	{
		PhysicsMessage msg = m_message_board->popMessage();

		switch (msg.type)
		{
		case PMessageType::SET_RIGID_BODY:

			m_rigid_bodies[msg.object_ID] = msg.rigid_body;
			m_colevel_rigid_bodies[msg.object_ID] = { {}, {} };

			// Kinda like an extra initialization
			msg.rigid_body->setTimeAfterTick(f_physics->getTimeStep());

			if (msg.rigid_body->getDampening() > 0)
			{
				m_dampening_objects.push_back(msg.rigid_body);
			}

			break;
		}
	}
}


void Jinny::PhysicsSystem::checkFriction()
{
	for (auto it = m_collisions.begin(); it != m_collisions.end(); it++)
	{
		if (it->is_horizontal_collision)
		{
			// Check for static or dynamic friction
			if (it->is_static_collision)
			{
				if (m_rigid_bodies[it->arrow_index]->getVelocity().y_value == 0)
				{
					double friction_force = it->force_applied * f_physics->getStaticFrictionCoefficient(m_rigid_bodies[it->arrow_index],
						m_rigid_bodies[it->target_index]);

					// Check if static friction for arrow
					if (abs(m_rigid_bodies[it->arrow_index]->getAppliedForce().y_value) > 0)
					{
						if (abs(friction_force) >= abs(m_rigid_bodies[it->arrow_index]->getAppliedForce().y_value))
						{
							m_rigid_bodies[it->arrow_index]->applySFForce({ 0, -m_rigid_bodies[it->arrow_index]->getAppliedForce().y_value });
						}
						else if (m_rigid_bodies[it->arrow_index]->getAppliedForce().y_value > 0)
						{
							m_rigid_bodies[it->arrow_index]->applySFForce({ 0, -friction_force });
						}
						else
						{
							m_rigid_bodies[it->arrow_index]->applySFForce({ 0, friction_force });
						}
					}
				}
				else
				{
					// Then dynamic friction
					double friction_force = it->force_applied * f_physics->getDynamicFrictionCoefficient(m_rigid_bodies[it->arrow_index],
						m_rigid_bodies[it->target_index]);

					double arrow_velocity_change = friction_force / m_rigid_bodies[it->arrow_index]->getMass() * f_physics->getTimeStep();
					if (arrow_velocity_change > abs(m_rigid_bodies[it->arrow_index]->getVelocity().y_value))
					{
						double zeroing_force = m_rigid_bodies[it->arrow_index]->getMass() * abs(m_rigid_bodies[it->arrow_index]->getVelocity().y_value) / f_physics->getTimeStep();
						if (m_rigid_bodies[it->arrow_index]->getVelocity().y_value > 0)
						{
							m_rigid_bodies[it->arrow_index]->applySFForce({ 0, -zeroing_force });
						}
						else
						{
							m_rigid_bodies[it->arrow_index]->applySFForce({ 0, zeroing_force });
						}
					}
					else if (m_rigid_bodies[it->arrow_index]->getVelocity().y_value > 0)
					{
						m_rigid_bodies[it->arrow_index]->applySFForce({ 0, -friction_force });
					}
					else
					{
						m_rigid_bodies[it->arrow_index]->applySFForce({ 0, friction_force });
					}
				}
			}
			else
			{
				if (m_rigid_bodies[it->arrow_index]->getVelocity().y_value == m_rigid_bodies[it->target_index]->getVelocity().y_value)
				{
					double friction_force = it->force_applied * f_physics->getStaticFrictionCoefficient(m_rigid_bodies[it->arrow_index],
						m_rigid_bodies[it->target_index]);

					// Check if static friction for arrow
					if (abs(m_rigid_bodies[it->arrow_index]->getAppliedForce().y_value) > 0)
					{
						if (abs(friction_force) >= abs(m_rigid_bodies[it->arrow_index]->getAppliedForce().y_value))
						{
							m_rigid_bodies[it->arrow_index]->applySFForce({ 0, -m_rigid_bodies[it->arrow_index]->getAppliedForce().y_value });
						}
						else if (m_rigid_bodies[it->arrow_index]->getAppliedForce().y_value > 0)
						{
							m_rigid_bodies[it->arrow_index]->applySFForce({ 0, -friction_force });
						}
						else
						{
							m_rigid_bodies[it->arrow_index]->applySFForce({ 0, friction_force });
						}
					}

					if (abs(m_rigid_bodies[it->target_index]->getAppliedForce().y_value) > 0)
					{
						if (abs(friction_force) >= abs(m_rigid_bodies[it->target_index]->getAppliedForce().y_value))
						{
							m_rigid_bodies[it->target_index]->applySFForce({ 0, -m_rigid_bodies[it->target_index]->getAppliedForce().y_value });
						}
						else if (m_rigid_bodies[it->target_index]->getAppliedForce().y_value > 0)
						{
							m_rigid_bodies[it->target_index]->applySFForce({ 0, -friction_force });
						}
						else
						{
							m_rigid_bodies[it->target_index]->applySFForce({ 0, friction_force });
						}
					}
				}
				else
				{
					// Then dynamic friction
					double friction_force = it->force_applied * f_physics->getDynamicFrictionCoefficient(m_rigid_bodies[it->arrow_index],
						m_rigid_bodies[it->target_index]);

					double relative_velocity = m_rigid_bodies[it->arrow_index]->getVelocity().y_value - m_rigid_bodies[it->target_index]->getVelocity().y_value;
					double arrow_velocity_change = friction_force / m_rigid_bodies[it->arrow_index]->getMass() * f_physics->getTimeStep();
					if (arrow_velocity_change > abs(relative_velocity))
					{
						double zeroing_force = m_rigid_bodies[it->arrow_index]->getMass() * abs(relative_velocity) / f_physics->getTimeStep();
						if (relative_velocity > 0)
						{
							m_rigid_bodies[it->arrow_index]->applySFForce({ 0, -zeroing_force });
						}
						else
						{
							m_rigid_bodies[it->arrow_index]->applySFForce({ 0, zeroing_force });
						}
					}
					else if (relative_velocity > 0)
					{
						m_rigid_bodies[it->arrow_index]->applySFForce({ 0, -friction_force });
					}
					else
					{
						m_rigid_bodies[it->arrow_index]->applySFForce({ 0, friction_force });
					}

					double target_velocity_change = friction_force / m_rigid_bodies[it->target_index]->getMass() * f_physics->getTimeStep();
					if (target_velocity_change > abs(relative_velocity))
					{
						double zeroing_force = m_rigid_bodies[it->target_index]->getMass() * abs(relative_velocity) / f_physics->getTimeStep();
						if (relative_velocity > 0)
						{
							m_rigid_bodies[it->target_index]->applySFForce({ 0, zeroing_force });
						}
						else
						{
							m_rigid_bodies[it->target_index]->applySFForce({ 0, -zeroing_force });
						}
					}
					else if (relative_velocity > 0)
					{
						m_rigid_bodies[it->target_index]->applySFForce({ 0, friction_force });
					}
					else
					{
						m_rigid_bodies[it->target_index]->applySFForce({ 0, -friction_force });
					}
				}
			}
		}
		// Else then horizontal
		else
		{
			// Check for static or dynamic friction
			if (it->is_static_collision)
			{
				if (m_rigid_bodies[it->arrow_index]->getVelocity().x_value == 0)
				{
					double friction_force = it->force_applied * f_physics->getStaticFrictionCoefficient(m_rigid_bodies[it->arrow_index],
						m_rigid_bodies[it->target_index]);

					// Check if static friction for arrow
					if (abs(m_rigid_bodies[it->arrow_index]->getAppliedForce().x_value) > 0)
					{
						if (abs(friction_force) >= abs(m_rigid_bodies[it->arrow_index]->getAppliedForce().x_value))
						{
							m_rigid_bodies[it->arrow_index]->applySFForce({ -m_rigid_bodies[it->arrow_index]->getAppliedForce().x_value, 0 });
						}
						else if (m_rigid_bodies[it->arrow_index]->getAppliedForce().x_value > 0)
						{
							m_rigid_bodies[it->arrow_index]->applySFForce({ -friction_force, 0 });
						}
						else
						{
							m_rigid_bodies[it->arrow_index]->applySFForce({ friction_force, 0 });
						}
					}
				}
				else
				{
					// Then dynamic friction
					double friction_force = it->force_applied * f_physics->getDynamicFrictionCoefficient(m_rigid_bodies[it->arrow_index],
						m_rigid_bodies[it->target_index]);

					double arrow_velocity_change = friction_force / m_rigid_bodies[it->arrow_index]->getMass() * f_physics->getTimeStep();
					if (arrow_velocity_change > abs(m_rigid_bodies[it->arrow_index]->getVelocity().x_value))
					{
						double zeroing_force = m_rigid_bodies[it->arrow_index]->getMass() * abs(m_rigid_bodies[it->arrow_index]->getVelocity().x_value) / f_physics->getTimeStep();
						if (m_rigid_bodies[it->arrow_index]->getVelocity().x_value > 0)
						{
							m_rigid_bodies[it->arrow_index]->applySFForce({ -zeroing_force, 0 });
						}
						else
						{
							m_rigid_bodies[it->arrow_index]->applySFForce({ zeroing_force, 0 });
						}
					}
					else if (m_rigid_bodies[it->arrow_index]->getVelocity().x_value > 0)
					{
						m_rigid_bodies[it->arrow_index]->applySFForce({ -friction_force, 0 });
					}
					else
					{
						m_rigid_bodies[it->arrow_index]->applySFForce({ friction_force, 0 });
					}
				}
			}
			else
			{
				if (m_rigid_bodies[it->arrow_index]->getVelocity().x_value == m_rigid_bodies[it->target_index]->getVelocity().x_value)
				{
					double friction_force = it->force_applied * f_physics->getStaticFrictionCoefficient(m_rigid_bodies[it->arrow_index],
						m_rigid_bodies[it->target_index]);

					// Check if static friction for arrow
					if (abs(m_rigid_bodies[it->arrow_index]->getAppliedForce().x_value) > 0)
					{
						if (abs(friction_force) >= abs(m_rigid_bodies[it->arrow_index]->getAppliedForce().x_value))
						{
							m_rigid_bodies[it->arrow_index]->applySFForce({ -m_rigid_bodies[it->arrow_index]->getAppliedForce().x_value, 0 });
						}
						else if (m_rigid_bodies[it->arrow_index]->getAppliedForce().x_value > 0)
						{
							m_rigid_bodies[it->arrow_index]->applySFForce({ -friction_force, 0 });
						}
						else
						{
							m_rigid_bodies[it->arrow_index]->applySFForce({ friction_force, 0 });
						}
					}

					if (abs(m_rigid_bodies[it->target_index]->getAppliedForce().x_value) > 0)
					{
						if (abs(friction_force) >= abs(m_rigid_bodies[it->target_index]->getAppliedForce().x_value))
						{
							m_rigid_bodies[it->target_index]->applySFForce({ -m_rigid_bodies[it->target_index]->getAppliedForce().y_value, 0 });
						}
						else if (m_rigid_bodies[it->target_index]->getAppliedForce().x_value > 0)
						{
							m_rigid_bodies[it->target_index]->applySFForce({ -friction_force, 0 });
						}
						else
						{
							m_rigid_bodies[it->target_index]->applySFForce({ friction_force, 0 });
						}
					}
				}
				else
				{
					// Then dynamic friction
					double friction_force = it->force_applied * f_physics->getDynamicFrictionCoefficient(m_rigid_bodies[it->arrow_index],
						m_rigid_bodies[it->target_index]);

					double relative_velocity = m_rigid_bodies[it->arrow_index]->getVelocity().x_value - m_rigid_bodies[it->target_index]->getVelocity().x_value;
					double arrow_velocity_change = friction_force / m_rigid_bodies[it->arrow_index]->getMass() * f_physics->getTimeStep();
					if (arrow_velocity_change > abs(relative_velocity))
					{
						double zeroing_force = m_rigid_bodies[it->arrow_index]->getMass() * abs(relative_velocity) / f_physics->getTimeStep();
						if (relative_velocity > 0)
						{
							m_rigid_bodies[it->arrow_index]->applySFForce({ -zeroing_force, 0 });
						}
						else
						{
							m_rigid_bodies[it->arrow_index]->applySFForce({ zeroing_force, 0 });
						}
					}
					else if (relative_velocity > 0)
					{
						m_rigid_bodies[it->arrow_index]->applySFForce({ -friction_force, 0 });
					}
					else
					{
						m_rigid_bodies[it->arrow_index]->applySFForce({ friction_force, 0 });
					}

					double target_velocity_change = friction_force / m_rigid_bodies[it->target_index]->getMass() * f_physics->getTimeStep();
					if (target_velocity_change > abs(relative_velocity))
					{
						double zeroing_force = m_rigid_bodies[it->target_index]->getMass() * abs(relative_velocity) / f_physics->getTimeStep();
						if (relative_velocity > 0)
						{
							m_rigid_bodies[it->target_index]->applySFForce({ zeroing_force, 0 });
						}
						else
						{
							m_rigid_bodies[it->target_index]->applySFForce({ -zeroing_force, 0 });
						}
					}
					else if (relative_velocity > 0)
					{
						m_rigid_bodies[it->target_index]->applySFForce({ friction_force, 0 });
					}
					else
					{
						m_rigid_bodies[it->target_index]->applySFForce({ -friction_force, 0 });
					}
				}
			}
		}
	}

	for (auto it = m_past_collisions.begin(); it != m_past_collisions.end(); it++)
	{
		if (it->is_horizontal_collision)
		{
			// Check for static or dynamic friction
			if (it->is_static_collision)
			{
				if (m_rigid_bodies[it->arrow_index]->getVelocity().y_value == 0)
				{
					double friction_force = it->force_applied * f_physics->getStaticFrictionCoefficient(m_rigid_bodies[it->arrow_index],
						m_rigid_bodies[it->target_index]);

					// Check if static friction for arrow
					if (abs(m_rigid_bodies[it->arrow_index]->getAppliedForce().y_value) > 0)
					{
						if (abs(friction_force) >= abs(m_rigid_bodies[it->arrow_index]->getAppliedForce().y_value))
						{
							m_rigid_bodies[it->arrow_index]->applySFForce({ 0, -m_rigid_bodies[it->arrow_index]->getAppliedForce().y_value });
						}
						else if (m_rigid_bodies[it->arrow_index]->getAppliedForce().y_value > 0)
						{
							m_rigid_bodies[it->arrow_index]->applySFForce({ 0, -friction_force });
						}
						else
						{
							m_rigid_bodies[it->arrow_index]->applySFForce({ 0, friction_force });
						}
					}
				}
				else
				{
					// Then dynamic friction
					double friction_force = it->force_applied * f_physics->getDynamicFrictionCoefficient(m_rigid_bodies[it->arrow_index],
						m_rigid_bodies[it->target_index]);

					double arrow_velocity_change = friction_force / m_rigid_bodies[it->arrow_index]->getMass() * f_physics->getTimeStep();
					if (arrow_velocity_change > abs(m_rigid_bodies[it->arrow_index]->getVelocity().y_value))
					{
						double zeroing_force = m_rigid_bodies[it->arrow_index]->getMass() * abs(m_rigid_bodies[it->arrow_index]->getVelocity().y_value) / f_physics->getTimeStep();
						if (m_rigid_bodies[it->arrow_index]->getVelocity().y_value > 0)
						{
							m_rigid_bodies[it->arrow_index]->applySFForce({ 0, -zeroing_force });
						}
						else
						{
							m_rigid_bodies[it->arrow_index]->applySFForce({ 0, zeroing_force });
						}
					}
					else if (m_rigid_bodies[it->arrow_index]->getVelocity().y_value > 0)
					{
						m_rigid_bodies[it->arrow_index]->applySFForce({ 0, -friction_force });
					}
					else
					{
						m_rigid_bodies[it->arrow_index]->applySFForce({ 0, friction_force });
					}
				}
			}
			else
			{
				if (m_rigid_bodies[it->arrow_index]->getVelocity().y_value == m_rigid_bodies[it->target_index]->getVelocity().y_value)
				{
					double friction_force = it->force_applied * f_physics->getStaticFrictionCoefficient(m_rigid_bodies[it->arrow_index],
						m_rigid_bodies[it->target_index]);

					// Check if static friction for arrow
					if (abs(m_rigid_bodies[it->arrow_index]->getAppliedForce().y_value) > 0)
					{
						if (abs(friction_force) >= abs(m_rigid_bodies[it->arrow_index]->getAppliedForce().y_value))
						{
							m_rigid_bodies[it->arrow_index]->applySFForce({ 0, -m_rigid_bodies[it->arrow_index]->getAppliedForce().y_value });
						}
						else if (m_rigid_bodies[it->arrow_index]->getAppliedForce().y_value > 0)
						{
							m_rigid_bodies[it->arrow_index]->applySFForce({ 0, -friction_force });
						}
						else
						{
							m_rigid_bodies[it->arrow_index]->applySFForce({ 0, friction_force });
						}
					}

					if (abs(m_rigid_bodies[it->target_index]->getAppliedForce().y_value) > 0)
					{
						if (abs(friction_force) >= abs(m_rigid_bodies[it->target_index]->getAppliedForce().y_value))
						{
							m_rigid_bodies[it->target_index]->applySFForce({ 0, -m_rigid_bodies[it->target_index]->getAppliedForce().y_value });
						}
						else if (m_rigid_bodies[it->target_index]->getAppliedForce().y_value > 0)
						{
							m_rigid_bodies[it->target_index]->applySFForce({ 0, -friction_force });
						}
						else
						{
							m_rigid_bodies[it->target_index]->applySFForce({ 0, friction_force });
						}
					}
				}
				else
				{
					// Then dynamic friction
					double friction_force = it->force_applied * f_physics->getDynamicFrictionCoefficient(m_rigid_bodies[it->arrow_index],
						m_rigid_bodies[it->target_index]);

					double relative_velocity = m_rigid_bodies[it->arrow_index]->getVelocity().y_value - m_rigid_bodies[it->target_index]->getVelocity().y_value;
					double arrow_velocity_change = friction_force / m_rigid_bodies[it->arrow_index]->getMass() * f_physics->getTimeStep();
					if (arrow_velocity_change > abs(relative_velocity))
					{
						double zeroing_force = m_rigid_bodies[it->arrow_index]->getMass() * abs(relative_velocity) / f_physics->getTimeStep();
						if (relative_velocity > 0)
						{
							m_rigid_bodies[it->arrow_index]->applySFForce({ 0, -zeroing_force });
						}
						else
						{
							m_rigid_bodies[it->arrow_index]->applySFForce({ 0, zeroing_force });
						}
					}
					else if (relative_velocity > 0)
					{
						m_rigid_bodies[it->arrow_index]->applySFForce({ 0, -friction_force });
					}
					else
					{
						m_rigid_bodies[it->arrow_index]->applySFForce({ 0, friction_force });
					}

					double target_velocity_change = friction_force / m_rigid_bodies[it->target_index]->getMass() * f_physics->getTimeStep();
					if (target_velocity_change > abs(relative_velocity))
					{
						double zeroing_force = m_rigid_bodies[it->target_index]->getMass() * abs(relative_velocity) / f_physics->getTimeStep();
						if (relative_velocity > 0)
						{
							m_rigid_bodies[it->target_index]->applySFForce({ 0, zeroing_force });
						}
						else
						{
							m_rigid_bodies[it->target_index]->applySFForce({ 0, -zeroing_force });
						}
					}
					else if (relative_velocity > 0)
					{
						m_rigid_bodies[it->target_index]->applySFForce({ 0, friction_force });
					}
					else
					{
						m_rigid_bodies[it->target_index]->applySFForce({ 0, -friction_force });
					}
				}
			}
		}
		// Else then horizontal
		else
		{
			// Check for static or dynamic friction
			if (it->is_static_collision)
			{
				if (m_rigid_bodies[it->arrow_index]->getVelocity().x_value == 0)
				{
					double friction_force = it->force_applied * f_physics->getStaticFrictionCoefficient(m_rigid_bodies[it->arrow_index],
						m_rigid_bodies[it->target_index]);

					// Check if static friction for arrow
					if (abs(m_rigid_bodies[it->arrow_index]->getAppliedForce().x_value) > 0)
					{
						if (abs(friction_force) >= abs(m_rigid_bodies[it->arrow_index]->getAppliedForce().x_value))
						{
							m_rigid_bodies[it->arrow_index]->applySFForce({ -m_rigid_bodies[it->arrow_index]->getAppliedForce().x_value, 0 });
						}
						else if (m_rigid_bodies[it->arrow_index]->getAppliedForce().x_value > 0)
						{
							m_rigid_bodies[it->arrow_index]->applySFForce({ -friction_force, 0 });
						}
						else
						{
							m_rigid_bodies[it->arrow_index]->applySFForce({ friction_force, 0 });
						}
					}
				}
				else
				{
					// Then dynamic friction
					double friction_force = it->force_applied * f_physics->getDynamicFrictionCoefficient(m_rigid_bodies[it->arrow_index],
						m_rigid_bodies[it->target_index]);

					double arrow_velocity_change = friction_force / m_rigid_bodies[it->arrow_index]->getMass() * f_physics->getTimeStep();
					if (arrow_velocity_change > abs(m_rigid_bodies[it->arrow_index]->getVelocity().x_value))
					{
						double zeroing_force = m_rigid_bodies[it->arrow_index]->getMass() * abs(m_rigid_bodies[it->arrow_index]->getVelocity().x_value) / f_physics->getTimeStep();
						if (m_rigid_bodies[it->arrow_index]->getVelocity().x_value > 0)
						{
							m_rigid_bodies[it->arrow_index]->applySFForce({ -zeroing_force, 0 });
						}
						else
						{
							m_rigid_bodies[it->arrow_index]->applySFForce({ zeroing_force, 0 });
						}
					}
					else if (m_rigid_bodies[it->arrow_index]->getVelocity().x_value > 0)
					{
						m_rigid_bodies[it->arrow_index]->applySFForce({ -friction_force, 0 });
					}
					else
					{
						m_rigid_bodies[it->arrow_index]->applySFForce({ friction_force, 0 });
					}
				}
			}
			else
			{
				if (m_rigid_bodies[it->arrow_index]->getVelocity().x_value == m_rigid_bodies[it->target_index]->getVelocity().x_value)
				{
					double friction_force = it->force_applied * f_physics->getStaticFrictionCoefficient(m_rigid_bodies[it->arrow_index],
						m_rigid_bodies[it->target_index]);

					// Check if static friction for arrow
					if (abs(m_rigid_bodies[it->arrow_index]->getAppliedForce().x_value) > 0)
					{
						if (abs(friction_force) >= abs(m_rigid_bodies[it->arrow_index]->getAppliedForce().x_value))
						{
							m_rigid_bodies[it->arrow_index]->applySFForce({ -m_rigid_bodies[it->arrow_index]->getAppliedForce().x_value, 0 });
						}
						else if (m_rigid_bodies[it->arrow_index]->getAppliedForce().x_value > 0)
						{
							m_rigid_bodies[it->arrow_index]->applySFForce({ -friction_force, 0 });
						}
						else
						{
							m_rigid_bodies[it->arrow_index]->applySFForce({ friction_force, 0 });
						}
					}

					if (abs(m_rigid_bodies[it->target_index]->getAppliedForce().x_value) > 0)
					{
						if (abs(friction_force) >= abs(m_rigid_bodies[it->target_index]->getAppliedForce().x_value))
						{
							m_rigid_bodies[it->target_index]->applySFForce({ -m_rigid_bodies[it->target_index]->getAppliedForce().y_value, 0 });
						}
						else if (m_rigid_bodies[it->target_index]->getAppliedForce().x_value > 0)
						{
							m_rigid_bodies[it->target_index]->applySFForce({ -friction_force, 0 });
						}
						else
						{
							m_rigid_bodies[it->target_index]->applySFForce({ friction_force, 0 });
						}
					}
				}
				else
				{
					// Then dynamic friction
					double friction_force = it->force_applied * f_physics->getDynamicFrictionCoefficient(m_rigid_bodies[it->arrow_index],
						m_rigid_bodies[it->target_index]);

					double relative_velocity = m_rigid_bodies[it->arrow_index]->getVelocity().x_value - m_rigid_bodies[it->target_index]->getVelocity().x_value;
					double arrow_velocity_change = friction_force / m_rigid_bodies[it->arrow_index]->getMass() * f_physics->getTimeStep();
					if (arrow_velocity_change > abs(relative_velocity))
					{
						double zeroing_force = m_rigid_bodies[it->arrow_index]->getMass() * abs(relative_velocity) / f_physics->getTimeStep();
						if (relative_velocity > 0)
						{
							m_rigid_bodies[it->arrow_index]->applySFForce({ -zeroing_force, 0 });
						}
						else
						{
							m_rigid_bodies[it->arrow_index]->applySFForce({ zeroing_force, 0 });
						}
					}
					else if (relative_velocity > 0)
					{
						m_rigid_bodies[it->arrow_index]->applySFForce({ -friction_force, 0 });
					}
					else
					{
						m_rigid_bodies[it->arrow_index]->applySFForce({ friction_force, 0 });
					}

					double target_velocity_change = friction_force / m_rigid_bodies[it->target_index]->getMass() * f_physics->getTimeStep();
					if (target_velocity_change > abs(relative_velocity))
					{
						double zeroing_force = m_rigid_bodies[it->target_index]->getMass() * abs(relative_velocity) / f_physics->getTimeStep();
						if (relative_velocity > 0)
						{
							m_rigid_bodies[it->target_index]->applySFForce({ zeroing_force, 0 });
						}
						else
						{
							m_rigid_bodies[it->target_index]->applySFForce({ -zeroing_force, 0 });
						}
					}
					else if (relative_velocity > 0)
					{
						m_rigid_bodies[it->target_index]->applySFForce({ friction_force, 0 });
					}
					else
					{
						m_rigid_bodies[it->target_index]->applySFForce({ -friction_force, 0 });
					}
				}
			}
		}
	}
}

void Jinny::PhysicsSystem::checkDampening()
{
	for (auto it = m_dampening_objects.begin(); it != m_dampening_objects.end(); it++)
	{
		f_physics->applyDampening((*it));
	}
}
