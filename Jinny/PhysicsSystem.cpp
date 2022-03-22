#include "PhysicsSystem.h"

#include "Physics.h"

#include "RigidBody.h"
#include "Shape.h"
#include <iostream>

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

	double tick_time = 0;

	// Check for intersections
	// May be slow in this part but can optimise later
	// If intersect then calculate collision of rigid bodies along both axises
	// Get earliest time and see if on same level in other axises,
	// Else do the same for the other axis
	// If collision then add to map of collisions

	// Loop only broken when no more collisions left
	while (true)
	{
		collision_loop:;

		m_collisions.clear();
		m_influence_rects.clear();

		// Calculate influence rects
		for (const auto rigid_body : m_rigid_bodies)
		{
			Framework::Vector size = Framework::Vector(rigid_body.second->getWidth(), rigid_body.second->getHeight());
			Framework::Vector position = rigid_body.second->getPosition();

			for (int axis : {0, 1})
			{
				double displacement = f_physics->getDisplacementAtTime(f_physics->getTimeStep() - tick_time, rigid_body.second->getVelocity()[axis],
					rigid_body.second->getAppliedForce()[axis] / rigid_body.second->getMass());

				if (displacement < 0)
				{
					position[axis] += displacement;
				}

				size[axis] += abs(displacement);
			}

			m_influence_rects.insert({ rigid_body.first, { position, size} });
		}

		// Iterate to find intersections
		for (auto it1 = m_influence_rects.begin(); it1 != m_influence_rects.end(); it1++)
		{
			// TODO: A bit janky 
			auto it2 = m_influence_rects.begin();
			int dist = std::distance(it2, it1);
			for (int i = 0; i < dist; i++)
			{
				it2++;
			}

			for (it2++; it2 != m_influence_rects.end(); it2++)
			{

				// Check if collision
				if (doesIntersect(it1->second, it2->second))
				{
					// Check if bodies are clipping
					InfluenceRectangle r[2];
					r[0]  = {m_rigid_bodies[it1->first]->getPosition(), m_rigid_bodies[it1->first]->getSize()};
					r[1] = {m_rigid_bodies[it2->first]->getPosition(), m_rigid_bodies[it2->first]->getSize()};
					if (doesIntersect(r[0], r[1]))
					{
						double smallest_distance = 1000000;
						int closest_axis = -1;
						int leftMost = -1;

						for (int axis : {0, 1})
						{
							for (int r_i : {0, 1})
							{
								double distance = r[r_i].position[axis] + r[r_i].size[axis] - r[1 - r_i].position[axis];

								if (distance < smallest_distance)
								{
									smallest_distance = distance;
									closest_axis = axis;
									leftMost = r_i;
								}
							}
						}

						if (m_rigid_bodies[it1->first]->isStatic() || m_rigid_bodies[it2->first]->isStatic())
						{
							Framework::RigidBody* dynamic_body = m_rigid_bodies[it1->first];
							int dynamic_id = 0;
							if (dynamic_body->isStatic())
							{
								dynamic_body = m_rigid_bodies[it2->first];
								dynamic_id = 1;
							}

							Framework::Vector new_position = dynamic_body->getPosition();

							if (dynamic_id == leftMost)
							{
								new_position[closest_axis] = r[1 - leftMost].position[closest_axis] - r[leftMost].size[closest_axis];
							}
							else
							{
								new_position[closest_axis] = r[leftMost].position[closest_axis] + r[leftMost].size[closest_axis];
							}

							if (new_position[closest_axis] < 0)
							{
								std::cout << "debug" << std::endl;
							}

							dynamic_body->setPosition(new_position);
						}
						else
						{
							Framework::Vector movement = { 0, 0 };
							movement[closest_axis] = smallest_distance / 2;
							if (leftMost == 0)
							{
								m_rigid_bodies[it1->first]->move(movement * -1);
								m_rigid_bodies[it2->first]->move(movement);
							}
							else
							{
								m_rigid_bodies[it2->first]->move(movement * -1);
								m_rigid_bodies[it1->first]->move(movement);

							}
						}

						goto collision_loop;
						// Could be a problem of having object clip into another object by fixing this clipping issue
					}

					// Get time of collision
					double collision_times[2] = { 0, 0 };
					for (int axis : {0, 1})
					{
						double distance = 0;
						if (m_rigid_bodies[it2->first]->getPosition()[axis] < m_rigid_bodies[it1->first]->getPosition()[axis])
						{
							distance = m_rigid_bodies[it1->first]->getPosition()[axis] - m_rigid_bodies[it2->first]->getPosition()[axis] - m_rigid_bodies[it2->first]->getSize()[axis];

						}
						else
						{
							distance = m_rigid_bodies[it2->first]->getPosition()[axis] - m_rigid_bodies[it1->first]->getPosition()[axis] - m_rigid_bodies[it1->first]->getSize()[axis];
						}

						if (m_rigid_bodies[it1->first]->getPosition()[axis] < m_rigid_bodies[it2->first]->getPosition()[axis])
						{
							collision_times[axis] = m_col_manager->getCollisionTime(distance, m_rigid_bodies[it1->first]->getVelocity()[axis], m_rigid_bodies[it2->first]->getVelocity()[axis],
								m_rigid_bodies[it1->first]->getAppliedForce()[axis] / m_rigid_bodies[it1->first]->getMass(),
								m_rigid_bodies[it2->first]->getAppliedForce()[axis] / m_rigid_bodies[it2->first]->getMass(), f_physics->getTimeStep() - tick_time);
						}
						else
						{
							collision_times[axis] = m_col_manager->getCollisionTime(distance, m_rigid_bodies[it2->first]->getVelocity()[axis], m_rigid_bodies[it1->first]->getVelocity()[axis],
								m_rigid_bodies[it2->first]->getAppliedForce()[axis] / m_rigid_bodies[it2->first]->getMass(),
								m_rigid_bodies[it1->first]->getAppliedForce()[axis] / m_rigid_bodies[it1->first]->getMass(), f_physics->getTimeStep() - tick_time);

						}

						if (collision_times[axis] > f_physics->getTimeStep() - tick_time)
						{
							collision_times[axis] = -1;
						}
					}

					// Check if objects are touching at time
					int smallest = 0;
					int largest = 1;

					if (collision_times[0] > collision_times[1])
					{
						smallest = 1;
						largest = 0;
					}

					for (int axis : {smallest, largest})
					{
						// TODO: don't like this
						if (collision_times[axis] >= 0) 
						{
							double displacement1 = f_physics->getDisplacementAtTime(collision_times[axis], m_rigid_bodies[it1->first]->getVelocity()[1 - axis],
								m_rigid_bodies[it1->first]->getAppliedForce()[1 - axis] / m_rigid_bodies[it1->first]->getMass());
							double displacement2 = f_physics->getDisplacementAtTime(collision_times[axis], m_rigid_bodies[it2->first]->getVelocity()[1 - axis],
								m_rigid_bodies[it2->first]->getAppliedForce()[1 - axis] / m_rigid_bodies[it2->first]->getMass());

							// Check if on same level (pretty sure this math is correct)
							// +1 to stop corner problems
							if (displacement1 + it1->second.position[1 - axis] <= displacement2 + it2->second.position[1 - axis] + it2->second.size[1 - axis] + 1 ||
								displacement2 + it2->second.position[1 - axis] <= displacement1 + it1->second.position[1 - axis] + it1->second.size[1 - axis] + 1)
							{
								if (m_collisions.size() > 0)
								{
									if (m_collisions[0].time > collision_times[axis])
									{
										m_collisions.clear();
										m_collisions.push_back({ collision_times[axis], axis, {m_rigid_bodies[it1->first], m_rigid_bodies[it2->first]}});
									}
									else if (m_collisions[0].time == collision_times[axis])
									{
										m_collisions.push_back({ collision_times[axis], axis, {m_rigid_bodies[it1->first], m_rigid_bodies[it2->first]}});
									}
								}
								else
								{
									m_collisions.push_back({ collision_times[axis], axis, {m_rigid_bodies[it1->first], m_rigid_bodies[it2->first]}});
								}

								break;
							}
						}
					}
				}
			}
		}

		// Break when no collisions left
		if (m_collisions.size() == 0)
		{
			break;
		}

		// Move objects to new positon at most recent collision time
		for (auto it = m_rigid_bodies.begin(); it != m_rigid_bodies.end(); it++)
		{
			it->second->move(f_physics->getDisplacementAtTime(m_collisions[0].time, it->second->getVelocity(),
				it->second->getAppliedForce() / it->second->getMass()));
			it->second->increaseVelocity(it->second->getAppliedForce() * m_collisions[0].time / it->second->getMass());
		}
		tick_time += m_collisions[0].time;

		// Iterate through collisions
		for (int it = 0; it < m_collisions.size(); it++)
		{
			// Calculate velocities of most recent collision
			if (m_collisions[it].rigid_bodies[0]->isStatic() || m_collisions[it].rigid_bodies[1]->isStatic())
			{
				Framework::RigidBody* dynamic_body = m_collisions[it].rigid_bodies[0];
				if (m_collisions[it].rigid_bodies[0]->isStatic())
				{
					dynamic_body = m_collisions[it].rigid_bodies[1];
				}

				Framework::Vector normal = dynamic_body->getAppliedForce() * -2;
				normal[1 - m_collisions[it].axis] = 0;

				dynamic_body->applySFForce(normal);
				
				Framework::Vector collision_force = Framework::Vector();
				collision_force[m_collisions[it].axis] = m_col_manager->calculateStaticCollisionForces(dynamic_body->getVelocity()[m_collisions[it].axis], dynamic_body->getMass(),
					f_physics->getCoefficientOfRestitution(m_collisions[it].rigid_bodies[0], m_collisions[it].rigid_bodies[1]), f_physics->getTimeStep() - tick_time);

				dynamic_body->increaseVelocity(collision_force / dynamic_body->getMass() * (f_physics->getTimeStep() - tick_time));
			}
			else
			{
				Framework::Vector normal1 = m_collisions[it].rigid_bodies[0]->getAppliedForce() * -1;
				normal1[1 - m_collisions[it].axis] = 0;
				Framework::Vector normal2 = m_collisions[it].rigid_bodies[1]->getAppliedForce() * -1;
				normal2[1 - m_collisions[it].axis] = 0;

				m_collisions[it].rigid_bodies[0]->applySFForce(normal1 + normal2 * -1);
				m_collisions[it].rigid_bodies[1]->applySFForce(normal2 + normal1 * -1);

				std::pair<double, double> collision_forces = m_col_manager->calculateDynamicCollisionForces(m_collisions[it].rigid_bodies[0]->getVelocity()[m_collisions[0].axis],
					m_collisions[it].rigid_bodies[0]->getMass(), m_collisions[it].rigid_bodies[1]->getVelocity()[m_collisions[0].axis],
					m_collisions[it].rigid_bodies[1]->getMass(),
					f_physics->getCoefficientOfRestitution(m_collisions[it].rigid_bodies[0], m_collisions[it].rigid_bodies[1]),
					f_physics->getTimeStep() - tick_time);

				Framework::Vector collision_force1 = Framework::Vector();
				collision_force1[m_collisions[it].axis] = collision_forces.first;
				Framework::Vector collision_force2 = Framework::Vector();
				collision_force2[m_collisions[it].axis] = collision_forces.second;

				m_collisions[it].rigid_bodies[0]->increaseVelocity(collision_force1 / m_collisions[it].rigid_bodies[0]->getMass() * (f_physics->getTimeStep() - tick_time));
				m_collisions[it].rigid_bodies[1]->increaseVelocity(collision_force2 / m_collisions[it].rigid_bodies[1]->getMass() * (f_physics->getTimeStep() - tick_time));
			}
		}
	}

	// Move the objects by the remaining time
	// Move objects to new positon at most recent collision time
    for (auto it = m_rigid_bodies.begin(); it != m_rigid_bodies.end(); it++)
	{
		it->second->move(f_physics->getDisplacementAtTime(f_physics->getTimeStep() - tick_time, it->second->getVelocity(),
			it->second->getAppliedForce() / it->second->getMass()));
		it->second->increaseVelocity(it->second->getAppliedForce() * (f_physics->getTimeStep() - tick_time) / it->second->getMass());

		// Clear single tick forces
		it->second->clearSFForce();
	}
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

bool Jinny::PhysicsSystem::doesIntersect(InfluenceRectangle r1, InfluenceRectangle r2)
{
	// Check if intersects
	for (int axis : {0, 1})
	{
		if (r1.position[axis] >= r2.position[axis] + r2.size[axis] || 
			r2.position[axis] >= r1.position[axis] + r1.size[axis])
		{
			return false;
		}
	}
	return true;
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
