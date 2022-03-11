#pragma once

#include "PhysicsComponent.h"

namespace Framework
{
	class RigidBody;
	class RigidBody;
}
namespace Jinny
{
	// Just Creates Border for world;
	class PlayerPhysicsComponent : public PhysicsComponent
	{
	public:

		// Constructor
		PlayerPhysicsComponent(double mass, double max_x_speed, double max_y_speed);

		void initialize(GameObject& object);

		void update();

		~PlayerPhysicsComponent();

	private:
		void handleEvents();
		void handleMessages();

		Framework::RigidBody* m_rigid_body;
		Framework::RigidBody* m_data;
	};

}