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

	// Calculate influence rects

	// Check for intersections
	// May be slow in this part but can optimise later

	// If intersect then calculate collision of rigid bodies along both axises
	// Get earliest time and see if on same level in other axises,
	// Else do the same for the other axis

	// If collision then add to map of collisions

	// Then get earliest collision and calculate new velocity

	// Move objects to new position in time and then recalculate influence rects and repeat

	// Until time passed and no collisions left
	
	// Friction and damping I'll worry about later
}

void Jinny::PhysicsSystem::close()
{
}

void Jinny::PhysicsSystem::handleMessages()
{
	// NOTE: for simplicity, physics based objects cannot be gui objects 

	// Pop all messages from message board
	int size = m_message_board->getQueueSize();
	for (int it = 0; it < size; it++)
	{
		PhysicsMessage msg = m_message_board->popMessage();

		switch (msg.type)
		{
		case PMessageType::SET_RIGID_BODY:
			m_rigid_bodies[msg.object_ID] = msg.rigid_body;
			break;
		}
	}
}


// What a horrible looking function, could do so much better

//void Jinny::PhysicsSystem::checkFriction()
//{
//	for (auto it = m_collisions.begin(); it != m_collisions.end(); it++)
//	{
//		if (it->is_horizontal_collision)
//		{
//			// Check for static or dynamic friction
//			if (it->is_static_collision)
//			{
//				if (m_rigid_bodies[it->arrow_index]->getVelocity().y == 0)
//				{
//					double friction_force = it->force_applied * f_physics->getStaticFrictionCoefficient(m_rigid_bodies[it->arrow_index],
//						m_rigid_bodies[it->target_index]);
//
//					// Check if static friction for arrow
//					if (abs(m_rigid_bodies[it->arrow_index]->getAppliedForce().y) > 0)
//					{
//						if (abs(friction_force) >= abs(m_rigid_bodies[it->arrow_index]->getAppliedForce().y))
//						{
//							m_rigid_bodies[it->arrow_index]->applySFForce({ 0, -m_rigid_bodies[it->arrow_index]->getAppliedForce().y });
//						}
//						else if (m_rigid_bodies[it->arrow_index]->getAppliedForce().y > 0)
//						{
//							m_rigid_bodies[it->arrow_index]->applySFForce({ 0, -friction_force });
//						}
//						else
//						{
//							m_rigid_bodies[it->arrow_index]->applySFForce({ 0, friction_force });
//						}
//					}
//				}
//				else
//				{
//					// Then dynamic friction
//					double friction_force = it->force_applied * f_physics->getDynamicFrictionCoefficient(m_rigid_bodies[it->arrow_index],
//						m_rigid_bodies[it->target_index]);
//
//					double arrow_velocity_change = friction_force / m_rigid_bodies[it->arrow_index]->getMass() * f_physics->getTimeStep();
//					if (arrow_velocity_change > abs(m_rigid_bodies[it->arrow_index]->getVelocity().y))
//					{
//						double zeroing_force = m_rigid_bodies[it->arrow_index]->getMass() * abs(m_rigid_bodies[it->arrow_index]->getVelocity().y) / f_physics->getTimeStep();
//						if (m_rigid_bodies[it->arrow_index]->getVelocity().y > 0)
//						{
//							m_rigid_bodies[it->arrow_index]->applySFForce({ 0, -zeroing_force });
//						}
//						else
//						{
//							m_rigid_bodies[it->arrow_index]->applySFForce({ 0, zeroing_force });
//						}
//					}
//					else if (m_rigid_bodies[it->arrow_index]->getVelocity().y > 0)
//					{
//						m_rigid_bodies[it->arrow_index]->applySFForce({ 0, -friction_force });
//					}
//					else
//					{
//						m_rigid_bodies[it->arrow_index]->applySFForce({ 0, friction_force });
//					}
//				}
//			}
//			else
//			{
//				if (m_rigid_bodies[it->arrow_index]->getVelocity().y == m_rigid_bodies[it->target_index]->getVelocity().y)
//				{
//					double friction_force = it->force_applied * f_physics->getStaticFrictionCoefficient(m_rigid_bodies[it->arrow_index],
//						m_rigid_bodies[it->target_index]);
//
//					// Check if static friction for arrow
//					if (abs(m_rigid_bodies[it->arrow_index]->getAppliedForce().y) > 0)
//					{
//						if (abs(friction_force) >= abs(m_rigid_bodies[it->arrow_index]->getAppliedForce().y))
//						{
//							m_rigid_bodies[it->arrow_index]->applySFForce({ 0, -m_rigid_bodies[it->arrow_index]->getAppliedForce().y });
//						}
//						else if (m_rigid_bodies[it->arrow_index]->getAppliedForce().y > 0)
//						{
//							m_rigid_bodies[it->arrow_index]->applySFForce({ 0, -friction_force });
//						}
//						else
//						{
//							m_rigid_bodies[it->arrow_index]->applySFForce({ 0, friction_force });
//						}
//					}
//
//					if (abs(m_rigid_bodies[it->target_index]->getAppliedForce().y) > 0)
//					{
//						if (abs(friction_force) >= abs(m_rigid_bodies[it->target_index]->getAppliedForce().y))
//						{
//							m_rigid_bodies[it->target_index]->applySFForce({ 0, -m_rigid_bodies[it->target_index]->getAppliedForce().y });
//						}
//						else if (m_rigid_bodies[it->target_index]->getAppliedForce().y > 0)
//						{
//							m_rigid_bodies[it->target_index]->applySFForce({ 0, -friction_force });
//						}
//						else
//						{
//							m_rigid_bodies[it->target_index]->applySFForce({ 0, friction_force });
//						}
//					}
//				}
//				else
//				{
//					// Then dynamic friction
//					double friction_force = it->force_applied * f_physics->getDynamicFrictionCoefficient(m_rigid_bodies[it->arrow_index],
//						m_rigid_bodies[it->target_index]);
//
//					double relative_velocity = m_rigid_bodies[it->arrow_index]->getVelocity().y - m_rigid_bodies[it->target_index]->getVelocity().y;
//					double arrow_velocity_change = friction_force / m_rigid_bodies[it->arrow_index]->getMass() * f_physics->getTimeStep();
//					if (arrow_velocity_change > abs(relative_velocity))
//					{
//						double zeroing_force = m_rigid_bodies[it->arrow_index]->getMass() * abs(relative_velocity) / f_physics->getTimeStep();
//						if (relative_velocity > 0)
//						{
//							m_rigid_bodies[it->arrow_index]->applySFForce({ 0, -zeroing_force });
//						}
//						else
//						{
//							m_rigid_bodies[it->arrow_index]->applySFForce({ 0, zeroing_force });
//						}
//					}
//					else if (relative_velocity > 0)
//					{
//						m_rigid_bodies[it->arrow_index]->applySFForce({ 0, -friction_force });
//					}
//					else
//					{
//						m_rigid_bodies[it->arrow_index]->applySFForce({ 0, friction_force });
//					}
//
//					double target_velocity_change = friction_force / m_rigid_bodies[it->target_index]->getMass() * f_physics->getTimeStep();
//					if (target_velocity_change > abs(relative_velocity))
//					{
//						double zeroing_force = m_rigid_bodies[it->target_index]->getMass() * abs(relative_velocity) / f_physics->getTimeStep();
//						if (relative_velocity > 0)
//						{
//							m_rigid_bodies[it->target_index]->applySFForce({ 0, zeroing_force });
//						}
//						else
//						{
//							m_rigid_bodies[it->target_index]->applySFForce({ 0, -zeroing_force });
//						}
//					}
//					else if (relative_velocity > 0)
//					{
//						m_rigid_bodies[it->target_index]->applySFForce({ 0, friction_force });
//					}
//					else
//					{
//						m_rigid_bodies[it->target_index]->applySFForce({ 0, -friction_force });
//					}
//				}
//			}
//		}
//		// Else then horizontal
//		else
//		{
//			// Check for static or dynamic friction
//			if (it->is_static_collision)
//			{
//				if (m_rigid_bodies[it->arrow_index]->getVelocity().x == 0)
//				{
//					double friction_force = it->force_applied * f_physics->getStaticFrictionCoefficient(m_rigid_bodies[it->arrow_index],
//						m_rigid_bodies[it->target_index]);
//
//					// Check if static friction for arrow
//					if (abs(m_rigid_bodies[it->arrow_index]->getAppliedForce().x) > 0)
//					{
//						if (abs(friction_force) >= abs(m_rigid_bodies[it->arrow_index]->getAppliedForce().x))
//						{
//							m_rigid_bodies[it->arrow_index]->applySFForce({ -m_rigid_bodies[it->arrow_index]->getAppliedForce().x, 0 });
//						}
//						else if (m_rigid_bodies[it->arrow_index]->getAppliedForce().x > 0)
//						{
//							m_rigid_bodies[it->arrow_index]->applySFForce({ -friction_force, 0 });
//						}
//						else
//						{
//							m_rigid_bodies[it->arrow_index]->applySFForce({ friction_force, 0 });
//						}
//					}
//				}
//				else
//				{
//					// Then dynamic friction
//					double friction_force = it->force_applied * f_physics->getDynamicFrictionCoefficient(m_rigid_bodies[it->arrow_index],
//						m_rigid_bodies[it->target_index]);
//
//					double arrow_velocity_change = friction_force / m_rigid_bodies[it->arrow_index]->getMass() * f_physics->getTimeStep();
//					if (arrow_velocity_change > abs(m_rigid_bodies[it->arrow_index]->getVelocity().x))
//					{
//						double zeroing_force = m_rigid_bodies[it->arrow_index]->getMass() * abs(m_rigid_bodies[it->arrow_index]->getVelocity().x) / f_physics->getTimeStep();
//						if (m_rigid_bodies[it->arrow_index]->getVelocity().x > 0)
//						{
//							m_rigid_bodies[it->arrow_index]->applySFForce({ -zeroing_force, 0 });
//						}
//						else
//						{
//							m_rigid_bodies[it->arrow_index]->applySFForce({ zeroing_force, 0 });
//						}
//					}
//					else if (m_rigid_bodies[it->arrow_index]->getVelocity().x > 0)
//					{
//						m_rigid_bodies[it->arrow_index]->applySFForce({ -friction_force, 0 });
//					}
//					else
//					{
//						m_rigid_bodies[it->arrow_index]->applySFForce({ friction_force, 0 });
//					}
//				}
//			}
//			else
//			{
//				if (m_rigid_bodies[it->arrow_index]->getVelocity().x == m_rigid_bodies[it->target_index]->getVelocity().x)
//				{
//					double friction_force = it->force_applied * f_physics->getStaticFrictionCoefficient(m_rigid_bodies[it->arrow_index],
//						m_rigid_bodies[it->target_index]);
//
//					// Check if static friction for arrow
//					if (abs(m_rigid_bodies[it->arrow_index]->getAppliedForce().x) > 0)
//					{
//						if (abs(friction_force) >= abs(m_rigid_bodies[it->arrow_index]->getAppliedForce().x))
//						{
//							m_rigid_bodies[it->arrow_index]->applySFForce({ -m_rigid_bodies[it->arrow_index]->getAppliedForce().x, 0 });
//						}
//						else if (m_rigid_bodies[it->arrow_index]->getAppliedForce().x > 0)
//						{
//							m_rigid_bodies[it->arrow_index]->applySFForce({ -friction_force, 0 });
//						}
//						else
//						{
//							m_rigid_bodies[it->arrow_index]->applySFForce({ friction_force, 0 });
//						}
//					}
//
//					if (abs(m_rigid_bodies[it->target_index]->getAppliedForce().x) > 0)
//					{
//						if (abs(friction_force) >= abs(m_rigid_bodies[it->target_index]->getAppliedForce().x))
//						{
//							m_rigid_bodies[it->target_index]->applySFForce({ -m_rigid_bodies[it->target_index]->getAppliedForce().y, 0 });
//						}
//						else if (m_rigid_bodies[it->target_index]->getAppliedForce().x > 0)
//						{
//							m_rigid_bodies[it->target_index]->applySFForce({ -friction_force, 0 });
//						}
//						else
//						{
//							m_rigid_bodies[it->target_index]->applySFForce({ friction_force, 0 });
//						}
//					}
//				}
//				else
//				{
//					// Then dynamic friction
//					double friction_force = it->force_applied * f_physics->getDynamicFrictionCoefficient(m_rigid_bodies[it->arrow_index],
//						m_rigid_bodies[it->target_index]);
//
//					double relative_velocity = m_rigid_bodies[it->arrow_index]->getVelocity().x - m_rigid_bodies[it->target_index]->getVelocity().x;
//					double arrow_velocity_change = friction_force / m_rigid_bodies[it->arrow_index]->getMass() * f_physics->getTimeStep();
//					if (arrow_velocity_change > abs(relative_velocity))
//					{
//						double zeroing_force = m_rigid_bodies[it->arrow_index]->getMass() * abs(relative_velocity) / f_physics->getTimeStep();
//						if (relative_velocity > 0)
//						{
//							m_rigid_bodies[it->arrow_index]->applySFForce({ -zeroing_force, 0 });
//						}
//						else
//						{
//							m_rigid_bodies[it->arrow_index]->applySFForce({ zeroing_force, 0 });
//						}
//					}
//					else if (relative_velocity > 0)
//					{
//						m_rigid_bodies[it->arrow_index]->applySFForce({ -friction_force, 0 });
//					}
//					else
//					{
//						m_rigid_bodies[it->arrow_index]->applySFForce({ friction_force, 0 });
//					}
//
//					double target_velocity_change = friction_force / m_rigid_bodies[it->target_index]->getMass() * f_physics->getTimeStep();
//					if (target_velocity_change > abs(relative_velocity))
//					{
//						double zeroing_force = m_rigid_bodies[it->target_index]->getMass() * abs(relative_velocity) / f_physics->getTimeStep();
//						if (relative_velocity > 0)
//						{
//							m_rigid_bodies[it->target_index]->applySFForce({ zeroing_force, 0 });
//						}
//						else
//						{
//							m_rigid_bodies[it->target_index]->applySFForce({ -zeroing_force, 0 });
//						}
//					}
//					else if (relative_velocity > 0)
//					{
//						m_rigid_bodies[it->target_index]->applySFForce({ friction_force, 0 });
//					}
//					else
//					{
//						m_rigid_bodies[it->target_index]->applySFForce({ -friction_force, 0 });
//					}
//				}
//			}
//		}
//	}
//
//	for (auto it = m_past_collisions.begin(); it != m_past_collisions.end(); it++)
//	{
//		if (it->is_horizontal_collision)
//		{
//			// Check for static or dynamic friction
//			if (it->is_static_collision)
//			{
//				if (m_rigid_bodies[it->arrow_index]->getVelocity().y == 0)
//				{
//					double friction_force = it->force_applied * f_physics->getStaticFrictionCoefficient(m_rigid_bodies[it->arrow_index],
//						m_rigid_bodies[it->target_index]);
//
//					// Check if static friction for arrow
//					if (abs(m_rigid_bodies[it->arrow_index]->getAppliedForce().y) > 0)
//					{
//						if (abs(friction_force) >= abs(m_rigid_bodies[it->arrow_index]->getAppliedForce().y))
//						{
//							m_rigid_bodies[it->arrow_index]->applySFForce({ 0, -m_rigid_bodies[it->arrow_index]->getAppliedForce().y });
//						}
//						else if (m_rigid_bodies[it->arrow_index]->getAppliedForce().y > 0)
//						{
//							m_rigid_bodies[it->arrow_index]->applySFForce({ 0, -friction_force });
//						}
//						else
//						{
//							m_rigid_bodies[it->arrow_index]->applySFForce({ 0, friction_force });
//						}
//					}
//				}
//				else
//				{
//					// Then dynamic friction
//					double friction_force = it->force_applied * f_physics->getDynamicFrictionCoefficient(m_rigid_bodies[it->arrow_index],
//						m_rigid_bodies[it->target_index]);
//
//					double arrow_velocity_change = friction_force / m_rigid_bodies[it->arrow_index]->getMass() * f_physics->getTimeStep();
//					if (arrow_velocity_change > abs(m_rigid_bodies[it->arrow_index]->getVelocity().y))
//					{
//						double zeroing_force = m_rigid_bodies[it->arrow_index]->getMass() * abs(m_rigid_bodies[it->arrow_index]->getVelocity().y) / f_physics->getTimeStep();
//						if (m_rigid_bodies[it->arrow_index]->getVelocity().y > 0)
//						{
//							m_rigid_bodies[it->arrow_index]->applySFForce({ 0, -zeroing_force });
//						}
//						else
//						{
//							m_rigid_bodies[it->arrow_index]->applySFForce({ 0, zeroing_force });
//						}
//					}
//					else if (m_rigid_bodies[it->arrow_index]->getVelocity().y > 0)
//					{
//						m_rigid_bodies[it->arrow_index]->applySFForce({ 0, -friction_force });
//					}
//					else
//					{
//						m_rigid_bodies[it->arrow_index]->applySFForce({ 0, friction_force });
//					}
//				}
//			}
//			else
//			{
//				if (m_rigid_bodies[it->arrow_index]->getVelocity().y == m_rigid_bodies[it->target_index]->getVelocity().y)
//				{
//					double friction_force = it->force_applied * f_physics->getStaticFrictionCoefficient(m_rigid_bodies[it->arrow_index],
//						m_rigid_bodies[it->target_index]);
//
//					// Check if static friction for arrow
//					if (abs(m_rigid_bodies[it->arrow_index]->getAppliedForce().y) > 0)
//					{
//						if (abs(friction_force) >= abs(m_rigid_bodies[it->arrow_index]->getAppliedForce().y))
//						{
//							m_rigid_bodies[it->arrow_index]->applySFForce({ 0, -m_rigid_bodies[it->arrow_index]->getAppliedForce().y });
//						}
//						else if (m_rigid_bodies[it->arrow_index]->getAppliedForce().y > 0)
//						{
//							m_rigid_bodies[it->arrow_index]->applySFForce({ 0, -friction_force });
//						}
//						else
//						{
//							m_rigid_bodies[it->arrow_index]->applySFForce({ 0, friction_force });
//						}
//					}
//
//					if (abs(m_rigid_bodies[it->target_index]->getAppliedForce().y) > 0)
//					{
//						if (abs(friction_force) >= abs(m_rigid_bodies[it->target_index]->getAppliedForce().y))
//						{
//							m_rigid_bodies[it->target_index]->applySFForce({ 0, -m_rigid_bodies[it->target_index]->getAppliedForce().y });
//						}
//						else if (m_rigid_bodies[it->target_index]->getAppliedForce().y > 0)
//						{
//							m_rigid_bodies[it->target_index]->applySFForce({ 0, -friction_force });
//						}
//						else
//						{
//							m_rigid_bodies[it->target_index]->applySFForce({ 0, friction_force });
//						}
//					}
//				}
//				else
//				{
//					// Then dynamic friction
//					double friction_force = it->force_applied * f_physics->getDynamicFrictionCoefficient(m_rigid_bodies[it->arrow_index],
//						m_rigid_bodies[it->target_index]);
//
//					double relative_velocity = m_rigid_bodies[it->arrow_index]->getVelocity().y - m_rigid_bodies[it->target_index]->getVelocity().y;
//					double arrow_velocity_change = friction_force / m_rigid_bodies[it->arrow_index]->getMass() * f_physics->getTimeStep();
//					if (arrow_velocity_change > abs(relative_velocity))
//					{
//						double zeroing_force = m_rigid_bodies[it->arrow_index]->getMass() * abs(relative_velocity) / f_physics->getTimeStep();
//						if (relative_velocity > 0)
//						{
//							m_rigid_bodies[it->arrow_index]->applySFForce({ 0, -zeroing_force });
//						}
//						else
//						{
//							m_rigid_bodies[it->arrow_index]->applySFForce({ 0, zeroing_force });
//						}
//					}
//					else if (relative_velocity > 0)
//					{
//						m_rigid_bodies[it->arrow_index]->applySFForce({ 0, -friction_force });
//					}
//					else
//					{
//						m_rigid_bodies[it->arrow_index]->applySFForce({ 0, friction_force });
//					}
//
//					double target_velocity_change = friction_force / m_rigid_bodies[it->target_index]->getMass() * f_physics->getTimeStep();
//					if (target_velocity_change > abs(relative_velocity))
//					{
//						double zeroing_force = m_rigid_bodies[it->target_index]->getMass() * abs(relative_velocity) / f_physics->getTimeStep();
//						if (relative_velocity > 0)
//						{
//							m_rigid_bodies[it->target_index]->applySFForce({ 0, zeroing_force });
//						}
//						else
//						{
//							m_rigid_bodies[it->target_index]->applySFForce({ 0, -zeroing_force });
//						}
//					}
//					else if (relative_velocity > 0)
//					{
//						m_rigid_bodies[it->target_index]->applySFForce({ 0, friction_force });
//					}
//					else
//					{
//						m_rigid_bodies[it->target_index]->applySFForce({ 0, -friction_force });
//					}
//				}
//			}
//		}
//		// Else then horizontal
//		else
//		{
//			// Check for static or dynamic friction
//			if (it->is_static_collision)
//			{
//				if (m_rigid_bodies[it->arrow_index]->getVelocity().x == 0)
//				{
//					double friction_force = it->force_applied * f_physics->getStaticFrictionCoefficient(m_rigid_bodies[it->arrow_index],
//						m_rigid_bodies[it->target_index]);
//
//					// Check if static friction for arrow
//					if (abs(m_rigid_bodies[it->arrow_index]->getAppliedForce().x) > 0)
//					{
//						if (abs(friction_force) >= abs(m_rigid_bodies[it->arrow_index]->getAppliedForce().x))
//						{
//							m_rigid_bodies[it->arrow_index]->applySFForce({ -m_rigid_bodies[it->arrow_index]->getAppliedForce().x, 0 });
//						}
//						else if (m_rigid_bodies[it->arrow_index]->getAppliedForce().x > 0)
//						{
//							m_rigid_bodies[it->arrow_index]->applySFForce({ -friction_force, 0 });
//						}
//						else
//						{
//							m_rigid_bodies[it->arrow_index]->applySFForce({ friction_force, 0 });
//						}
//					}
//				}
//				else
//				{
//					// Then dynamic friction
//					double friction_force = it->force_applied * f_physics->getDynamicFrictionCoefficient(m_rigid_bodies[it->arrow_index],
//						m_rigid_bodies[it->target_index]);
//
//					double arrow_velocity_change = friction_force / m_rigid_bodies[it->arrow_index]->getMass() * f_physics->getTimeStep();
//					if (arrow_velocity_change > abs(m_rigid_bodies[it->arrow_index]->getVelocity().x))
//					{
//						double zeroing_force = m_rigid_bodies[it->arrow_index]->getMass() * abs(m_rigid_bodies[it->arrow_index]->getVelocity().x) / f_physics->getTimeStep();
//						if (m_rigid_bodies[it->arrow_index]->getVelocity().x > 0)
//						{
//							m_rigid_bodies[it->arrow_index]->applySFForce({ -zeroing_force, 0 });
//						}
//						else
//						{
//							m_rigid_bodies[it->arrow_index]->applySFForce({ zeroing_force, 0 });
//						}
//					}
//					else if (m_rigid_bodies[it->arrow_index]->getVelocity().x > 0)
//					{
//						m_rigid_bodies[it->arrow_index]->applySFForce({ -friction_force, 0 });
//					}
//					else
//					{
//						m_rigid_bodies[it->arrow_index]->applySFForce({ friction_force, 0 });
//					}
//				}
//			}
//			else
//			{
//				if (m_rigid_bodies[it->arrow_index]->getVelocity().x == m_rigid_bodies[it->target_index]->getVelocity().x)
//				{
//					double friction_force = it->force_applied * f_physics->getStaticFrictionCoefficient(m_rigid_bodies[it->arrow_index],
//						m_rigid_bodies[it->target_index]);
//
//					// Check if static friction for arrow
//					if (abs(m_rigid_bodies[it->arrow_index]->getAppliedForce().x) > 0)
//					{
//						if (abs(friction_force) >= abs(m_rigid_bodies[it->arrow_index]->getAppliedForce().x))
//						{
//							m_rigid_bodies[it->arrow_index]->applySFForce({ -m_rigid_bodies[it->arrow_index]->getAppliedForce().x, 0 });
//						}
//						else if (m_rigid_bodies[it->arrow_index]->getAppliedForce().x > 0)
//						{
//							m_rigid_bodies[it->arrow_index]->applySFForce({ -friction_force, 0 });
//						}
//						else
//						{
//							m_rigid_bodies[it->arrow_index]->applySFForce({ friction_force, 0 });
//						}
//					}
//
//					if (abs(m_rigid_bodies[it->target_index]->getAppliedForce().x) > 0)
//					{
//						if (abs(friction_force) >= abs(m_rigid_bodies[it->target_index]->getAppliedForce().x))
//						{
//							m_rigid_bodies[it->target_index]->applySFForce({ -m_rigid_bodies[it->target_index]->getAppliedForce().y, 0 });
//						}
//						else if (m_rigid_bodies[it->target_index]->getAppliedForce().x > 0)
//						{
//							m_rigid_bodies[it->target_index]->applySFForce({ -friction_force, 0 });
//						}
//						else
//						{
//							m_rigid_bodies[it->target_index]->applySFForce({ friction_force, 0 });
//						}
//					}
//				}
//				else
//				{
//					// Then dynamic friction
//					double friction_force = it->force_applied * f_physics->getDynamicFrictionCoefficient(m_rigid_bodies[it->arrow_index],
//						m_rigid_bodies[it->target_index]);
//
//					double relative_velocity = m_rigid_bodies[it->arrow_index]->getVelocity().x - m_rigid_bodies[it->target_index]->getVelocity().x;
//					double arrow_velocity_change = friction_force / m_rigid_bodies[it->arrow_index]->getMass() * f_physics->getTimeStep();
//					if (arrow_velocity_change > abs(relative_velocity))
//					{
//						double zeroing_force = m_rigid_bodies[it->arrow_index]->getMass() * abs(relative_velocity) / f_physics->getTimeStep();
//						if (relative_velocity > 0)
//						{
//							m_rigid_bodies[it->arrow_index]->applySFForce({ -zeroing_force, 0 });
//						}
//						else
//						{
//							m_rigid_bodies[it->arrow_index]->applySFForce({ zeroing_force, 0 });
//						}
//					}
//					else if (relative_velocity > 0)
//					{
//						m_rigid_bodies[it->arrow_index]->applySFForce({ -friction_force, 0 });
//					}
//					else
//					{
//						m_rigid_bodies[it->arrow_index]->applySFForce({ friction_force, 0 });
//					}
//
//					double target_velocity_change = friction_force / m_rigid_bodies[it->target_index]->getMass() * f_physics->getTimeStep();
//					if (target_velocity_change > abs(relative_velocity))
//					{
//						double zeroing_force = m_rigid_bodies[it->target_index]->getMass() * abs(relative_velocity) / f_physics->getTimeStep();
//						if (relative_velocity > 0)
//						{
//							m_rigid_bodies[it->target_index]->applySFForce({ zeroing_force, 0 });
//						}
//						else
//						{
//							m_rigid_bodies[it->target_index]->applySFForce({ -zeroing_force, 0 });
//						}
//					}
//					else if (relative_velocity > 0)
//					{
//						m_rigid_bodies[it->target_index]->applySFForce({ friction_force, 0 });
//					}
//					else
//					{
//						m_rigid_bodies[it->target_index]->applySFForce({ -friction_force, 0 });
//					}
//				}
//			}
//		}
//	}
//}

//void Jinny::PhysicsSystem::checkDampening()
//{
	//for (auto it = m_dampening_objects.begin(); it != m_dampening_objects.end(); it++)
	//{
		//f_physics->applyDampening((*it));
	//}
//}
