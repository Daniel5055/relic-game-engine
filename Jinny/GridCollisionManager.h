#pragma once

#include <map>
#include <vector>
#include <utility>

#include "RigidBody.h"
#include "ExactDecimal.h"

namespace Framework
{
	class Physics;
}

namespace Jinny
{
	class GridCollisionManager
	{
	public:
		// Constructor
		GridCollisionManager(Framework::Physics* physics, std::map<int, Framework::RigidBody*>& list);

		void initialize();

		void updateCollisions();

	private:

		// Struct to contain collision data
		struct Collision
		{

			double time;

			int a_index;
			int t_index;

			bool is_horizontal;

			double force_applied;
		};


		std::map<int, Framework::RigidBody*>& m_rigid_bodies;

		std::vector<int> m_moved_rigid_bodies;
		std::map<int, int> m_corner_potentials;

		std::vector<Collision> m_collisions;

		std::map<int, std::pair<std::vector<int>, std::vector<int>>> m_colevel_bodies;

		// Framework Dependencies
		Framework::Physics* f_physics;
		double f_max_time_step;
		double f_ppm;

		// --- Internal Functions ---

		// Checking if two objects are on the same level
		bool onSameXLevel(Framework::RigidBody* body_1, Framework::RigidBody* body_2);
		bool onSameYLevel(Framework::RigidBody* body_1, Framework::RigidBody* body_2);

		// Check if a collision occurs, returns time of collision if true
		double checkXCollision(Framework::RigidBody* arrow, Framework::RigidBody* target);
		double checkYCollision(Framework::RigidBody* arrow, Framework::RigidBody* target);

		// Called when corner collision happenes, returns time of collision
		double getCornerCollisionTime(Framework::RigidBody* arrow, Framework::RigidBody* target);

		// Determines the time of collision between two objects on a single axis
		double getCollisionTime(Framework::eDec distance, double velocity_1, double velocity_2, double acceleration_1, double acceleration_2, double max_time);

		// Calculate resultant force on objects in dynamic collision
		std::pair<double, double> calculateDynamicCollisionForces(double a_velocity, double a_mass, double t_velocity, double t_mass, double coeff_restitution);
		double calculateStaticCollisionForce(double axis_velocity, double mass, double coeff_restitution);

		// Deterime movement at time
		Framework::eDec getMovementAtTime(double time, double velocity, double acceleration);

	};
}