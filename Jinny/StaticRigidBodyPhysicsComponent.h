#pragma once

#include "PhysicsComponent.h"

#include "Material.h"

namespace Framework
{
	class RigidBody;

}

namespace Jinny
{
	class StaticRigidBodyPhysicsComponent : public PhysicsComponent
	{
	public:
		// Constructor
		StaticRigidBodyPhysicsComponent(Framework::Material material = Framework::Material::NULLIUM);

		// Initialize
		virtual void initialize(GameObject& object);

		// Destructor
		~StaticRigidBodyPhysicsComponent();

	private:
		// --- Data ---
		Framework::RigidBody* m_rigid_body;

		Framework::Material m_material;
	};
}