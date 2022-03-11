#pragma once

#include <utility>

#include "Vector.h"
#include "MaterialManager.h"
#include "ExactDecimal.h"

namespace Framework
{
	class RigidBody;

	class Physics
	{
	public:
		// Constructor
		Physics(double time_step, double ppm, double x_dampin);

		// Destructor
		~Physics();

		// Get Time Step
		double getTimeStep() const;
		double getPPM() const;

		// Perfroms physics on data, returns supposed distance moved as vector in pixels
		Vector nextStep(RigidBody* physics_data);

		// For calculating collision positions
		double getDisplacementAtTime(double time, double axis_velocity, double axis_acceleration);
		Vector getDisplacementAtTime(double time, Vector velocity, Vector acceleration);

		// For calculating forces of collisions
		double getCoefficientOfRestitution(RigidBody* rigid_body_1, RigidBody* rigid_body_2);

		void applyDampening(RigidBody* data);
		
		// For corner collisions checking
		double getDynamicCollisionTime(RigidBody* arrow_body, RigidBody* arrow_physics, RigidBody* target_body, RigidBody* target_physics, double max_time);
		double getStaticCollisionTime(RigidBody* arrow_body, RigidBody* arrow_physics, RigidBody* target_body);

		// Friction
		double getStaticFrictionCoefficient(RigidBody* rigid_body_1, RigidBody* rigid_body_2);
		double getDynamicFrictionCoefficient(RigidBody* rigid_body_1, RigidBody* rigid_body_2);

	private:
		// --- Data ---
		MaterialManager* m_material_manager;

		// --- Const Data ---
		const double TIME_STEP;
		const double PIXELS_PER_METER;

		void setVelocityAtTime(RigidBody* data, double time);



	};


}