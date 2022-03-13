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
		//void checkDampening();

		// Checking friction
		//void checkFriction();

		// Message Board
		MessageBoard<PhysicsMessage>* m_message_board;

		// Framework
		Framework::Physics* f_physics;

		GridCollisionManager* m_col_manager;

		// Map of object IDs and their rigid bodies
		std::map<int, Framework::RigidBody*> m_rigid_bodies;
		
		double m_acceleration_due_to_gravity;
	};
}