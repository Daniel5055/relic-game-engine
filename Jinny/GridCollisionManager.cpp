#include "GridCollisionManager.h"

#include "Physics.h"

Jinny::GridCollisionManager::GridCollisionManager(Framework::Physics* physics, std::map<int, Framework::RigidBody*>& list)
	:m_rigid_bodies(list)
{
	f_physics = physics;
}

void Jinny::GridCollisionManager::initialize()
{
	f_max_time_step = f_physics->getTimeStep();
	f_ppm = f_physics->getPPM();
}

void Jinny::GridCollisionManager::updateCollisions()
{
	// Iterate through data
	for (auto it_1 = m_rigid_bodies.begin(); it_1 != m_rigid_bodies.end(); it_1++)
	{
		// Check if has movement
		if (!it_1->second->getXMovement() == 0 || !it_1->second->getYMovement() == 0)
		{
			m_moved_rigid_bodies.push_back(it_1->first);
			m_corner_potentials[it_1->first] = -1;

			// Iteratre through rest of rigid bodies
			for (auto it_2 = m_rigid_bodies.begin(); it_2 != m_rigid_bodies.end(); it_2++)
			{
				// Check that they are not the same object
				if (it_2 != it_1)
				{
					// Check if objects are on the same axis levels
					if (onSameYLevel(it_1->second, it_2->second))
					{
						m_colevel_bodies[it_1->first].first.push_back(it_2->first);
					}
					if (onSameXLevel(it_1->second, it_2->second))
					{
						m_colevel_bodies[it_1->first].second.push_back(it_2->first);
					}
				}
			}
		}
	}

	// Check collisions
	double time = f_max_time_step;

	// Standard collision
	Collision collision;

	bool is_corner_collision = false;

	while (true)
	{
		for (auto a_it = m_colevel_bodies.begin(); a_it != m_colevel_bodies.end(); a_it++)
		{
			// Iterate through objects on same y-level
			for (auto t_it = a_it->second.first.begin(); t_it != a_it->second.first.end(); t_it++)
			{
				double new_time = checkXCollision(m_rigid_bodies[a_it->first], m_rigid_bodies[*(t_it)]);
				if (new_time >= 0 && new_time < time)
				{
					time = new_time;
					collision.a_index = a_it->first;
					collision.t_index = *t_it;
					collision.time = new_time;
					collision.is_horizontal = true;

					is_corner_collision = false;
				}
				else if (new_time == -2)
				{
					// Means there was a missed collision, if there are two of these for a collision pair then there is a corner collision
					m_corner_potentials[a_it->first] = *t_it;
				}
			}

			// Iterate through objects on same x-level
			for (auto t_it = a_it->second.second.begin(); t_it != a_it->second.second.end(); t_it++)
			{
				double new_time = checkYCollision(m_rigid_bodies[a_it->first], m_rigid_bodies[*(t_it)]);
				if (new_time >= 0 && new_time < time)
				{
					time = new_time;
					collision.a_index = a_it->first;
					collision.t_index = *t_it;
					collision.time = new_time;
					collision.is_horizontal = false;

					is_corner_collision = false;
				}
				else if (new_time == -2)
				{
					// Means there was a missed collision, if there are two of these for a collision pair then there is a corner collision

					// Check is missed collision on other axis
					if (m_corner_potentials[a_it->first] == *t_it)
					{
						// If true then calculate collision time
						new_time = getCornerCollisionTime(m_rigid_bodies[a_it->first], m_rigid_bodies[*t_it]);

						// checks if earliest collision
						if (new_time < time)
						{
							time = new_time;
							collision.a_index = a_it->first;
							collision.t_index = *t_it;
							collision.time = new_time;
							collision.is_horizontal = false;

							is_corner_collision = true;
						}
					}
				}
			}
		}

		if (time < f_max_time_step)
		{
			if (is_corner_collision == true)
			{
				// Reset corner collision
				is_corner_collision = false;

				// Set new tick movements for arrows
				m_rigid_bodies[collision.a_index]->setXMovement(getMovementAtTime(time, m_rigid_bodies[collision.a_index]->getVelocity().x, m_rigid_bodies[collision.a_index]->getAppliedForce().x / m_rigid_bodies[collision.a_index]->getMass()));
				m_rigid_bodies[collision.a_index]->setYMovement(getMovementAtTime(time, m_rigid_bodies[collision.a_index]->getVelocity().y, m_rigid_bodies[collision.a_index]->getAppliedForce().y / m_rigid_bodies[collision.a_index]->getMass()));

				// Set time of collision for arrow
				m_rigid_bodies[collision.a_index]->setTimeAfterTick(collision.time);

				// Make sure target hasnt already collided
				if (collision.time < m_rigid_bodies[collision.t_index]->getTimeAfterTick())
				{
					m_rigid_bodies[collision.t_index]->setXMovement(getMovementAtTime(time, m_rigid_bodies[collision.t_index]->getVelocity().x, m_rigid_bodies[collision.t_index]->getAppliedForce().x / m_rigid_bodies[collision.t_index]->getMass()));
					m_rigid_bodies[collision.t_index]->setYMovement(getMovementAtTime(time, m_rigid_bodies[collision.t_index]->getVelocity().y, m_rigid_bodies[collision.t_index]->getAppliedForce().y / m_rigid_bodies[collision.t_index]->getMass()));

					// Set time of collision for target
					m_rigid_bodies[collision.t_index]->setTimeAfterTick(collision.time);
				}
				

				// Adds corner collision to collisions as equivalent to horizontal and vertical collision
				collision.is_horizontal = true;
				m_collisions.push_back(collision);

				collision.is_horizontal = false;
				m_collisions.push_back(collision);
			}
			else if (collision.is_horizontal)
			{
				// Set new tick movement for arrow
				m_rigid_bodies[collision.a_index]->setXMovement(getMovementAtTime(time, m_rigid_bodies[collision.a_index]->getVelocity().x, m_rigid_bodies[collision.a_index]->getAppliedForce().x / m_rigid_bodies[collision.a_index]->getMass()));

				// Set time of collision for arrow
				m_rigid_bodies[collision.a_index]->setTimeAfterTick(collision.time);

				// Make sure target hasnt already collided
				if (collision.time < m_rigid_bodies[collision.t_index]->getTimeAfterTick())
				{
					m_rigid_bodies[collision.t_index]->setXMovement(getMovementAtTime(time, m_rigid_bodies[collision.t_index]->getVelocity().x, m_rigid_bodies[collision.t_index]->getAppliedForce().x / m_rigid_bodies[collision.t_index]->getMass()));

					// Set time of collision for target
					m_rigid_bodies[collision.t_index]->setTimeAfterTick(collision.time);
				}
				

				// Add collision to collisions
				m_collisions.push_back(collision);
			}
			else
			{
				// Set new tick movement for arrow
				m_rigid_bodies[collision.a_index]->setYMovement(getMovementAtTime(time, m_rigid_bodies[collision.a_index]->getVelocity().y, m_rigid_bodies[collision.a_index]->getAppliedForce().y / m_rigid_bodies[collision.a_index]->getMass()));

				// Set time of collision for arrow
				m_rigid_bodies[collision.a_index]->setTimeAfterTick(collision.time);

				// Make sure target hasnt already collided
				if (collision.time < m_rigid_bodies[collision.t_index]->getTimeAfterTick())
				{
					m_rigid_bodies[collision.t_index]->setYMovement(getMovementAtTime(time, m_rigid_bodies[collision.t_index]->getVelocity().y, m_rigid_bodies[collision.t_index]->getAppliedForce().y / m_rigid_bodies[collision.t_index]->getMass()));

					// Set time of collision for target
					m_rigid_bodies[collision.t_index]->setTimeAfterTick(collision.time);
				}


				// Add collision to collisions
				m_collisions.push_back(collision);
			}
				
			
		}
		else
		{
			break;
		}
	}


	// Apply velocities and stuff
	for (auto it = m_moved_rigid_bodies.begin(); it != m_moved_rigid_bodies.end(); it++)
	{
		// Apply final velocities
		m_rigid_bodies[*it]->increaseVelocity(m_rigid_bodies[*it]->getAppliedForce() / m_rigid_bodies[*it]->getMass() * m_rigid_bodies[*it]->getTimeAfterTick());

		// Reset sf forces // !!!!!!!!!!!!!!!!!!!!!!!! Warning, this might be Source of Error
		m_rigid_bodies[*it]->clearSFForce();

		// Time Step not needed anymore
		m_rigid_bodies[*it]->setTimeAfterTick(f_max_time_step);
	}


	// Collision handling
	for (auto it = m_collisions.begin(); it != m_collisions.end(); it++)
	{
		double coeff_of_restitution = f_physics->getCoefficientOfRestitution(m_rigid_bodies[it->a_index], m_rigid_bodies[it->t_index]);
		if (it->is_horizontal)
		{
			if (m_rigid_bodies[it->t_index]->isStatic())
			{
				double force = calculateStaticCollisionForce(m_rigid_bodies[it->a_index]->getVelocity().x, m_rigid_bodies[it->a_index]->getMass(), coeff_of_restitution);

				// Finds total force of collision and set as force applied
				it->force_applied = abs(force - (m_rigid_bodies[it->a_index]->getAppliedForce().x) - (m_rigid_bodies[it->a_index]->getMass() * m_rigid_bodies[it->a_index]->getVelocity().x / f_physics->getTimeStep()));

				m_rigid_bodies[it->a_index]->applySFForce({force - m_rigid_bodies[it->a_index]->getAppliedForce().x, 0 });

				// Prevents further movement through wall, "applySFForce" already notes that velocity is zero
				m_rigid_bodies[it->a_index]->stopXVelocity();
			}
			else
			{
				std::pair <double, double> forces = calculateDynamicCollisionForces(m_rigid_bodies[it->a_index]->getVelocity().x, m_rigid_bodies[it->a_index]->getMass(),
					m_rigid_bodies[it->t_index]->getVelocity().x, m_rigid_bodies[it->t_index]->getMass(), coeff_of_restitution);

				// Finds total force of collision and add to force applied
				it->force_applied = abs(forces.first - m_rigid_bodies[it->a_index]->getAppliedForce().x - (m_rigid_bodies[it->a_index]->getMass() * m_rigid_bodies[it->a_index]->getVelocity().x / f_physics->getTimeStep()));

				m_rigid_bodies[it->a_index]->applySFForce({ forces.first - m_rigid_bodies[it->a_index]->getAppliedForce().x , 0 });
				m_rigid_bodies[it->t_index]->applySFForce({ forces.second - m_rigid_bodies[it->t_index]->getAppliedForce().x, 0 });

				// Prevents further movement through wall, "applySFForce" already notes that velocity is zero
				m_rigid_bodies[it->a_index]->stopXVelocity();
				m_rigid_bodies[it->t_index]->stopXVelocity();
			}
		}
		else
		{
			if (m_rigid_bodies[it->t_index]->isStatic())
			{
				double force = calculateStaticCollisionForce(m_rigid_bodies[it->a_index]->getVelocity().y, m_rigid_bodies[it->a_index]->getMass(), coeff_of_restitution);

				// Finds total force of collision and add to force applied
				it->force_applied = abs(force - (m_rigid_bodies[it->a_index]->getAppliedForce().y) - (m_rigid_bodies[it->a_index]->getMass() * m_rigid_bodies[it->a_index]->getVelocity().y / f_physics->getTimeStep()));

				m_rigid_bodies[it->a_index]->applySFForce({ 0, force - m_rigid_bodies[it->a_index]->getAppliedForce().y });

				// Prevents further movement through wall, "applySFForce" already notes that velocity is zero
				m_rigid_bodies[it->a_index]->stopYVelocity();

			}
			else
			{

				std::pair <double, double> forces = calculateDynamicCollisionForces(m_rigid_bodies[it->a_index]->getVelocity().y, m_rigid_bodies[it->a_index]->getMass(),
					m_rigid_bodies[it->t_index]->getVelocity().y, m_rigid_bodies[it->t_index]->getMass(), coeff_of_restitution);

				// Finds total force of collision and add to force applied
				it->force_applied = abs(forces.first - m_rigid_bodies[it->a_index]->getAppliedForce().y - (m_rigid_bodies[it->a_index]->getMass() * m_rigid_bodies[it->a_index]->getVelocity().y / f_physics->getTimeStep()));

				m_rigid_bodies[it->a_index]->applySFForce({ 0, forces.first - m_rigid_bodies[it->a_index]->getAppliedForce().y });
				m_rigid_bodies[it->t_index]->applySFForce({ 0, forces.second - m_rigid_bodies[it->t_index]->getAppliedForce().y });



				// Prevents further movement through wall, "applySFForce" already notes that velocity is zero
				m_rigid_bodies[it->a_index]->stopYVelocity();
				m_rigid_bodies[it->t_index]->stopYVelocity();

			}
		}
	}
}

bool Jinny::GridCollisionManager::onSameXLevel(Framework::RigidBody* body_1, Framework::RigidBody* body_2)
{
	// Check if on same x-level
	if (body_1->getXMovement() >= 0)
	{
		if (body_2->getXMovement() >= 0)
		{
			// If both moving rightwards
			if (!(body_1->getXMovement() >= body_2->getX() + body_2->getWidth() + body_2->getXMovement() ||
				body_1->getX() + body_1->getWidth() + body_1->getXMovement() <= body_2->getX()))
			{
				return true;
			}
		}
		else
		{
			// If one moving up, one moving down
			if (!(body_1->getX() + body_1->getXMovement() >= body_2->getX() + body_2->getWidth() + body_2->getXMovement() ||
				body_1->getX() + body_1->getWidth() <= body_2->getX()))
			{
				return true;
			}
		}
	}
	else
	{
		if (body_2->getXMovement() >= 0)
		{
			// If one moving down, one moving up
			if (!(body_1->getX() >= body_2->getX() + body_2->getWidth() ||
				body_1->getX() + body_1->getWidth() + body_1->getXMovement() <= body_2->getX() + body_2->getXMovement()))
			{
				return true;
			}
		}
		else
		{
			// If both moving downwards
			if (!(body_1->getX() + body_1->getXMovement() >= body_2->getX() + body_2->getWidth() ||
				body_1->getX() + body_1->getWidth() <= body_2->getX() + body_2->getXMovement()))
			{
				return true;
			}
		}
	}

	return false;
}

bool Jinny::GridCollisionManager::onSameYLevel(Framework::RigidBody* body_1, Framework::RigidBody* body_2)
{
	// Check if on same y-level
	if (body_1->getYMovement() >= 0)
	{
		if (body_2->getYMovement() >= 0)
		{
			// If both moving downwards
			if (!(body_1->getYMovement() >= body_2->getY() + body_2->getHeight() + body_2->getYMovement() ||
				body_1->getY() + body_1->getHeight() + body_1->getYMovement()<= body_2->getY()))
			{
				return true;
			}
		}
		else
		{
			// If one moving down, one moving up
			if (!(body_1->getY() + body_1->getYMovement() >= body_2->getY() + body_2->getHeight() + body_2->getYMovement() ||
				body_1->getY() + body_1->getHeight() <= body_2->getY()))
			{
				return true;
			}
		}
	}
	else
	{
		if (body_2->getYMovement() >= 0)
		{
			// If one moving up, one moving down
			if (!(body_1->getY() >= body_2->getY() + body_2->getHeight() ||
				body_1->getY() + body_1->getHeight() + body_1->getYMovement() <= body_2->getY() + body_2->getYMovement()))
			{
				return true;
			}
		}
		else
		{
			// If both moving upwards
			if (!(body_1->getY() + body_1->getYMovement() >= body_2->getY() + body_2->getHeight() ||
				body_1->getY() + body_1->getHeight() <= body_2->getY() + body_2->getYMovement()))
			{
				return true;
			}
		}
	}

	return false;
}

double Jinny::GridCollisionManager::checkXCollision(Framework::RigidBody* arrow, Framework::RigidBody* target)
{
	double time = -1;
	double new_time;

	// If arrow going right
	if (arrow->getXMovement() > 0)
	{
		// Possible collision flag
		bool p_collision = false;

		// Where they go in the same direction
		if (target->getXMovement() >= 0)
		{
			if (arrow->getX() + arrow->getWidth() <= target->getX() &&
				arrow->getX() + arrow->getWidth() + arrow->getXMovement() > target->getX())
			{
				p_collision = true;
			}
		}
		else
		{
			// Where they go in opposite directions
			if (arrow->getX() + arrow->getWidth() <= target->getX() &&
				arrow->getX() + arrow->getWidth() + arrow->getXMovement() > target->getX() + target->getXMovement())
			{
				p_collision = true;
			}
		}

		// If Possible Collsion
		// Movement of target on later statement not included here as there are cases where this could miss collisions
		if (p_collision == true)
		{
			new_time = getCollisionTime(double(target->getX() - arrow->getX() - arrow->getWidth()),
				arrow->getVelocity().x, target->getVelocity().x,
				arrow->getAppliedForce().x / arrow->getMass(),
				target->getAppliedForce().x / target->getMass(), target->getTimeAfterTick());

			if (new_time < f_max_time_step && new_time >= 0)
			{
				// collision

				// Check if still on y level
				double y_arrow_moved = getMovementAtTime(new_time, arrow->getVelocity().y, arrow->getAppliedForce().y / arrow->getMass());
				double y_target_moved = getMovementAtTime(new_time, target->getVelocity().y, target->getAppliedForce().y / target->getMass());

				if (!(arrow->getY() + y_arrow_moved >= target->getY() + target->getHeight() + y_target_moved &&
					arrow->getY() + arrow->getHeight() + y_arrow_moved <= target->getY() + y_target_moved))
				{
					time = new_time;
				}
				else
				{
					// For corner potential
					time = -2;
				}
			}
		}
	}
	// If going left
	else if (arrow->getXMovement() < 0)
	{
		// Possible Collision flag
		bool p_collision = false;

		// Where they go in the same direction
		if (target->getXMovement() <= 0)
		{
			// Where they go in the same direction
			if (arrow->getX() >= target->getX() + target->getWidth() &&
				arrow->getX() + arrow->getXMovement() < target->getX() + target->getWidth())
			{
				p_collision = true;
			}
		}
		else
		{
			// Where they go in different directions
			if (arrow->getX() >= target->getX() + target->getWidth() &&
				arrow->getX() + arrow->getXMovement() < target->getX() + target->getWidth() + target->getXMovement())
			{
				p_collision = true;
			}
		}

		// If Possible Collsion
		// Movement of target on later staetement not included here as there are cases where this could miss collisions
		if (p_collision == true)
		{
			new_time = getCollisionTime(double(target->getX() + target->getWidth() - arrow->getX()),
				arrow->getVelocity().x, target->getVelocity().x,
				arrow->getAppliedForce().x / arrow->getMass(),
				target->getAppliedForce().x / target->getMass(), target->getTimeAfterTick());

			if (new_time < f_max_time_step && new_time >= 0)
			{
				// collision

				// Check if still on y level
				double y_arrow_moved = getMovementAtTime(new_time, arrow->getVelocity().y, arrow->getAppliedForce().y / arrow->getMass());
				double y_target_moved = getMovementAtTime(new_time, target->getVelocity().y, target->getAppliedForce().y / target->getMass());

				if (!(arrow->getY() + y_arrow_moved >= target->getY() + target->getHeight() + y_target_moved &&
					arrow->getY() + arrow->getHeight() + y_arrow_moved <= target->getY() + y_target_moved))
				{
					time = new_time;
				}
				else
				{
					// For corner potential
					time = -2;
				}
			}
		}
	}

	return time;
}

double Jinny::GridCollisionManager::checkYCollision(Framework::RigidBody* arrow, Framework::RigidBody* target)
{
	double time = -1;
	double new_time;

	// If arrow going down
	if (arrow->getYMovement() > 0)
	{
		// Possible collision flag
		bool p_collision = false;

		// Where they go in the same direction
		if (target->getYMovement() >= 0)
		{
			if (arrow->getY() + arrow->getHeight() <= target->getY() &&
				arrow->getY() + arrow->getHeight() + arrow->getYMovement() > target->getY())
			{
				p_collision = true;
			}
		}
		else
		{
			// Where they go in opposite directions
			if (arrow->getY() + arrow->getHeight() <= target->getY() &&
				arrow->getY() + arrow->getHeight() + arrow->getYMovement() > target->getY() + target->getYMovement())
			{
				p_collision = true;
			}
		}

		// If Possible Collsion
		// Movement of target on later statement not included here as there are cases where this could miss collisions
		if (p_collision == true)
		{
			new_time = getCollisionTime(double(target->getY() - arrow->getY() - arrow->getHeight()),
				arrow->getVelocity().y, target->getVelocity().y,
				arrow->getAppliedForce().y / arrow->getMass(),
				target->getAppliedForce().y / target->getMass(), target->getTimeAfterTick());

			if (new_time < f_max_time_step && new_time >= 0)
			{
				// collision

				// Check if still on y level
				double x_arrow_moved = getMovementAtTime(new_time, arrow->getVelocity().x, arrow->getAppliedForce().x / arrow->getMass());
				double x_target_moved = getMovementAtTime(new_time, target->getVelocity().x, target->getAppliedForce().x / target->getMass());

				if (!(arrow->getX() + x_arrow_moved >= target->getX() + target->getWidth() + x_target_moved &&
					arrow->getX() + arrow->getWidth() + x_arrow_moved <= target->getX() + x_target_moved))
				{
					time = new_time;
				}
				else
				{
					// For corner potential
					time = -2;
				}
			}
		}
	}
	// If going up
	else if (arrow->getYMovement() < 0)
	{
		// Possible Collision flag
		bool p_collision = false;

		// Where they go in the same direction
		if (target->getYMovement() <= 0)
		{
			// Where they go in the same direction
			if (arrow->getY() >= target->getY() + target->getHeight() &&
				arrow->getY() + arrow->getYMovement() < target->getY() + target->getHeight())
			{
				p_collision = true;
			}
		}
		else
		{
			// Where they go in different directions
			if (arrow->getY() >= target->getY() + target->getHeight() &&
				arrow->getY() + arrow->getYMovement() < target->getY() + target->getHeight() + target->getYMovement())
			{
				p_collision = true;
			}
		}

		// If Possible Collsion
		// Movement of target on later staetement not included here as there are cases where this could miss collisions
		if (p_collision == true)
		{
			new_time = getCollisionTime(double(target->getY() + target->getHeight() - arrow->getY()),
				arrow->getVelocity().y, target->getVelocity().y,
				arrow->getAppliedForce().y / arrow->getMass(),
				target->getAppliedForce().y / target->getMass(), target->getTimeAfterTick());

			if (new_time < f_max_time_step && new_time >= 0)
			{
				// collision

				// Check if still on y level
				double x_arrow_moved = getMovementAtTime(new_time, arrow->getVelocity().x, arrow->getAppliedForce().x / arrow->getMass());
				double x_target_moved = getMovementAtTime(new_time, target->getVelocity().x, target->getAppliedForce().x / target->getMass());

				if (!(arrow->getX() + x_arrow_moved >= target->getX() + target->getWidth() + x_target_moved &&
					arrow->getX() + arrow->getWidth() + x_arrow_moved <= target->getX() + x_target_moved))
				{
					time = new_time;
				}
				else
				{
					// For corner potential
					time = -2;
				}
			}
		}
	}

	return time;
}

double Jinny::GridCollisionManager::getCornerCollisionTime(Framework::RigidBody* arrow, Framework::RigidBody* target)
{
	if (arrow->getXMovement() > 0)
	{
		return getCollisionTime(double(target->getX() - arrow->getX() - arrow->getWidth()),
			arrow->getVelocity().x, target->getVelocity().x,
			arrow->getAppliedForce().x / arrow->getMass(),
			target->getAppliedForce().x / target->getMass(), target->getTimeAfterTick());
	}
	else
	{
		return getCollisionTime(double(target->getX() + target->getWidth() - arrow->getX()),
			arrow->getVelocity().x, target->getVelocity().x,
			arrow->getAppliedForce().x / arrow->getMass(),
			target->getAppliedForce().x / target->getMass(), target->getTimeAfterTick());
	}
}

double Jinny::GridCollisionManager::getCollisionTime(double distance, double velocity_1, double velocity_2, double acceleration_1, double acceleration_2, double max_time)
{
	// variable useful for some stuff here
	double time = -1;

	// Distance refers to target pos - arrow pos (can be negative (maybe i should say displacement))
	if ((acceleration_1 == acceleration_2))
	{
		// Physics formula for time which two colliding objects will hit using suvat and two objects

		time = ((distance / f_ppm) / (velocity_1 - velocity_2));
		if (time >= 0)
		{
			if (time > max_time)
			{
				// Because then axis_acceleration_2 must also be zero
				if (acceleration_1 != 0)
				{
					// Then redo calculations with max_time
					double max_distance = double(velocity_2 * max_time + 0.5 * acceleration_2 * pow(max_time, 2) + distance / f_ppm);

					double discriminant = pow(velocity_1, 2) + 2 * (max_distance) * (acceleration_1);

					if (discriminant < 0)
					{
						return -1;
					}

					double b_negative = (-velocity_1);
					double a = (acceleration_1);

					time = (b_negative - sqrt(discriminant)) / a;

					// Determining correct time (smallest non negative collision)
					if (time >= 0)
					{
						// Check other solution in case
						double other_time = (b_negative + sqrt(discriminant)) / a;
						if (other_time < time && other_time > 0)
						{
							return other_time;
						}
						else
						{
							return time;
						}
					}
					else
					{
						return (b_negative + sqrt(discriminant)) / a;
					}
				}
				else
				{
					return ((distance / f_ppm + velocity_2 * max_time) / (velocity_1));
				}

			}
			else
			{
				return time;
			}
		}
		else
		{
			if (acceleration_1 != 0)
			{
				// Then redo calculations with max_time
				double max_distance = double(velocity_2 * max_time + 0.5 * acceleration_2 * pow(max_time, 2) + distance / f_ppm);

				double discriminant = pow(velocity_1, 2) + 2 * (max_distance) * (acceleration_1);

				if (discriminant < 0)
				{
					return -1;
				}

				double b_negative = (-velocity_1);
				double a = (acceleration_1);

				time = (b_negative - sqrt(discriminant)) / a;

				// Determining correct time (smallest non negative collision)
				if (time >= 0)
				{
					// Check other solution in case
					double other_time = (b_negative + sqrt(discriminant)) / a;;
					if (other_time < time && other_time > 0)
					{
						return other_time;
					}
					else
					{
						return time;
					}
				}
				else
				{
					return (b_negative + sqrt(discriminant)) / a;
				}
			}
			else
			{
				return ((distance / f_ppm + velocity_2 * max_time) / (velocity_1));
			}
		}

	}

	// For cases where they are already in contact
	else if (distance == 0)
	{
		if ((velocity_1 > 0 && velocity_2 <= 0) || (velocity_1 < 0 && velocity_2 >= 0))
		{
			return 0;
		}
		else if (abs(velocity_1) > abs(velocity_2))
		{
			// Will collide
			return 0;
		}
		else if (abs(velocity_1) < abs(velocity_2))
		{
			// Will not collide
			return -1;
		}
		else
		{
			// equal to zero
			if ((acceleration_1 > 0 && acceleration_2 <= 0) || (acceleration_1 < 0 && acceleration_2 >= 0))
			{
				return 0;
			}
			else if (abs(acceleration_1) > abs(acceleration_2))
			{
				// Will collide
				return 0;
			}
			else
			{
				double max_distance = double(velocity_2 * max_time + 0.5 * acceleration_2 * pow(max_time, 2));

				double discriminant = pow(velocity_1, 2) + 2 * (max_distance) * (acceleration_1);

				if (discriminant < 0)
				{
					return -1;
				}

				double b_negative = (-velocity_1);
				double a = (acceleration_1);

				time = (b_negative - sqrt(discriminant)) / a;

				// Determining correct time (smallest non negative collision)
				if (time >= 0)
				{
					// Check other solution in case
					double other_time = (b_negative + sqrt(discriminant)) / a;;
					if (other_time < time && other_time > 0)
					{
						return other_time;
					}
					else
					{
						return time;
					}
				}
				else
				{
					return (b_negative + sqrt(discriminant)) / a;
				}

			}
		}
	}

	// Advanced suvat equation using quadratic formula

	double discriminant = pow(velocity_1 - velocity_2, 2) + 2 * (distance / f_ppm) * (acceleration_1 - acceleration_2);

	if (discriminant < 0)
	{
		double max_distance = double(velocity_2 * max_time + 0.5 * acceleration_2 * pow(max_time, 2));
		discriminant = pow(velocity_1, 2) + 2 * (distance / f_ppm + max_distance) * acceleration_1;

		if (discriminant < 0)
		{
			return -1;
		}

		time = (-velocity_1 - sqrt(discriminant)) / acceleration_1;

		// Same check as before for determining correct collision
		if (time >= 0)
		{
			// Check other solution in case
			double other_time = (-velocity_1 + sqrt(discriminant)) / acceleration_1;
			if (other_time < time && other_time > 0)
			{
				return other_time;
			}
			else
			{
				return time;
			}
		}
		else
		{
			return (-velocity_1 + sqrt(discriminant)) / acceleration_1;
		}
	}

	double b_negative = (velocity_2 - velocity_1);
	double a = (acceleration_1 - acceleration_2);

	time = (b_negative - sqrt(discriminant)) / a;

	// Determining correct time (smallest non negative collision)
	if (time >= 0)
	{
		// Check other solution in case
		double other_time = (b_negative + sqrt(discriminant)) / a;
		if (other_time < time && other_time > 0)
		{
			// Check if time is not greater than max
			if (time > max_time)
			{
				double max_distance = double(velocity_2 * max_time + 0.5 * acceleration_2 * pow(max_time, 2));
				discriminant = pow(velocity_1, 2) + 2 * (distance / f_ppm + max_distance) * acceleration_1;

				// Is this check neccessary? AAAAAAAAAAAAAAAAAAAA
				if (discriminant < 0)
				{
					return -1;
				}

				time = (-velocity_1 - sqrt(discriminant)) / acceleration_1;

				// Same check as before for determining correct collision
				if (time >= 0)
				{
					// Check other solution in case
					other_time = (b_negative + sqrt(discriminant)) / a;
					if (other_time < time && other_time > 0)
					{
						return other_time;
					}
					else
					{
						return time;
					}
				}
				else
				{
					return (-velocity_1 + sqrt(discriminant)) / acceleration_1;
				}
			}
			else
			{
				return time;
			}

		}

		// Check if time is not greater than max
		if (time > max_time)
		{
			double max_distance = double(velocity_2 * max_time + 0.5 * acceleration_2 * pow(max_time, 2));
			discriminant = pow(velocity_1, 2) + 2 * (distance / f_ppm + max_distance) * acceleration_1;

			// Is this check neccessary? AAAAAAAAAAAAAAAAAAAA
			if (discriminant < 0)
			{
				return -1;
			}

			time = (-velocity_1 - sqrt(discriminant)) / acceleration_1;

			// Same check as before for determining correct collision
			if (time >= 0)
			{
				// Check other solution in case
				double other_time = (-velocity_1 + sqrt(discriminant)) / acceleration_1;
				if (other_time < time && other_time > 0)
				{
					return other_time;
				}
				else
				{
					return time;
				}
			}
			else
			{
				return (-velocity_1 + sqrt(discriminant)) / acceleration_1;
			}
		}
		else
		{
			return time;
		}
	}
	else
	{
		time = (b_negative + sqrt(discriminant)) / a;

		// Check if time is not greater than max
		if (time > max_time)
		{
			double max_distance = double(velocity_2 * max_time + 0.5 * acceleration_2 * pow(max_time, 2));
			discriminant = pow(velocity_1, 2) + 2 * (distance / f_ppm + max_distance) * acceleration_1;

			// Is this check neccessary? AAAAAAAAAAAAAAAAAAAA
			if (discriminant < 0)
			{
				return -1;
			}

			time = (-velocity_1 - sqrt(discriminant)) / acceleration_1;

			// Same check as before for determining correct collision
			if (time >= 0)
			{
				// Check other solution in case
				double other_time = (-velocity_1 + sqrt(discriminant)) / acceleration_1;
				if (other_time < time && other_time > 0)
				{
					return other_time;
				}
				else
				{
					return time;
				}
			}
			else
			{
				return (-velocity_1 + sqrt(discriminant)) / acceleration_1;
			}
		}
		else
		{
			return time;
		}
	}

	// With regards to checking, I am not sure how many of the possibilities I have created are possible
}

std::pair<double, double> Jinny::GridCollisionManager::calculateDynamicCollisionForces(double a_velocity, double a_mass, double t_velocity, double t_mass, double coeff_restitution)
{
	double momentum = a_velocity * a_mass + t_velocity * t_mass;

	std::pair<double, double> out;

	double right_part = coeff_restitution * (a_velocity - t_velocity);
	double t_new_velocity = (momentum + a_mass * right_part) / (t_mass + a_mass);
	double a_new_velocity = (momentum - t_mass * right_part) / (t_mass + a_mass);

	out.first = a_mass * a_new_velocity / f_max_time_step;
	out.second = t_mass * t_new_velocity / f_max_time_step;

	return out;
}

double Jinny::GridCollisionManager::calculateStaticCollisionForce(double axis_velocity, double mass, double coeff_restitution)
{
	if (abs(axis_velocity) < 0.05)
	{
		return 0;
	}
	return (mass * -axis_velocity * coeff_restitution) / f_max_time_step;
}

double Jinny::GridCollisionManager::getMovementAtTime(double time, double velocity, double acceleration)
{
	return double(time * velocity + 0.5 * acceleration * time * time);
}
