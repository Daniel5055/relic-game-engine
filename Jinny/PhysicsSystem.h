#pragma once

#include <Vector>
#include <Map>
#include <utility>

#include "GameSystem.h"

#include "MessageBoard.h"
#include "PhysicsMessage.h"

#include "GridCollisionManager.h"

#include "Vector.h"

namespace Framework
{
	class Physics;
	class RigidBody;

	struct Shape;
}

namespace Jinny
{
	class PhysicsSystem : public GameSystem
	{
	public:
		// Constructor
		PhysicsSystem();
		// Initialize
		void intialize(Framework::Physics* physics, MessageBoard<PhysicsMessage>* message_board);

		// Updating
		void update();

		// Closing
		void close();
	private:
		void handleMessages();	

		// --- Internal Functions ---


		// Checking dampening
		void checkDampening();

		// Checking friction
		void checkFriction();

		// Message Board
		MessageBoard<PhysicsMessage>* m_message_board;

		// Framework
		Framework::Physics* f_physics;

		GridCollisionManager* m_col_manager;


		// --- Data ---

		struct Collision
		{
			double time;

			double force_applied;

			int arrow_index;
			int target_index;

			bool is_horizontal_collision;
			bool is_static_collision;

			// operator for comparison
			bool operator==(const Collision& collision)
			{
				if (arrow_index == collision.arrow_index && target_index == collision.target_index)
				{
					return true;
				}
				return false;
			}
		};

		// map of objects' index and physics data
		std::map<int, Framework::RigidBody*> m_data;

		// Map of object IDs and their rigid bodies
		std::map<int, Framework::RigidBody*> m_rigid_bodies;
		
		// --- Temp Data ---

		// Map of object IDs and their colevel pairs
		std::map<int, std::pair<std::vector<int>, std::vector<int>>> m_colevel_rigid_bodies;
		std::map<int, std::pair<std::vector<int>, std::vector<int>>> m_colevel_static_rigid_bodies;

		// Vector of moved physics data with rigid bodies
		std::vector<int> m_moved_rigid_bodies;

		// Map of object and its respective target it missed, if value != -1, then there was missed collision,
		// If this happens on both axis between the same pairs then there is corner potenial
		std::map<int, int> m_corner_potentials;
		std::vector<Collision> m_collisions;
		std::vector<Collision> m_past_collisions;

		// Dampening enabled objects
		std::vector<Framework::RigidBody*> m_dampening_objects;

		// Member which determines world boundary
		Framework::RigidBody* m_collision_boundary;

		double m_acceleration_due_to_gravity;

		
	};
}