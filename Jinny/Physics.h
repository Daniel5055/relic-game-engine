#pragma once

#include <utility>

#include "Vector.h"
#include "MaterialManager.h"

namespace Framework
{
	class RigidBody;

	// A class for handling or delegating various physics calculations
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

		// TODO: Seems redundant this
		Vector nextStep(RigidBody* physics_data);

		// For calculating collision positions
		double getDisplacementAtTime(double time, double axis_velocity, double axis_acceleration);
		Vector getDisplacementAtTime(double time, Vector velocity, Vector acceleration);

		// For calculating forces of collisions
		double getCoefficientOfRestitution(RigidBody* rigid_body_1, RigidBody* rigid_body_2);

		// TODO: need to improve this code
		void applyDampening(RigidBody* data);

		// Friction
		// TODO: why not just let them access material manager?
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