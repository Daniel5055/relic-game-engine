#pragma once

#include "Vector.h"
#include "Shape.h"

namespace Framework
{
	enum class Material;

	class RigidBody
	{
	public:
		// Constructor
		RigidBody(double mass, double dampening, Framework::Shape* shape_ptr, Framework::Material material);

		// Mass Accessors
		double getMass() const;
		void setMass(double mass);

		// Velocity Accessors
		Vector getVelocity() const;
		void increaseVelocity(Vector additional_velocity);
		void stopXVelocity();
		void stopYVelocity();
		void stopVelocity();
		bool isStationary() const;

		// Force Accessors
		Vector getAppliedForce();
		void applyMFForce(Vector force);
		void applySFForce(Vector force);
		void clearSFForce();

		// Dampening Accessor
		double getDampening() const;

		// Shape Accessors
		void setShape(Framework::Shape* shape_ptr);

		int getWidth() const;
		int getHeight() const;
		Vector getSize() const;
		Vector getPosition() const;
		void setPosition(Vector position);
		int getRoundedX() const;
		int getRoundedY() const;

		void move(Vector movement);

		// Static accessors
		bool isStatic() const;
		void setStatic(bool is_static);

		// Material 
		Material getMaterial() const;
	private:

		// Mass in kg
		double m_mass;

		// Current Velocity in meters per second
		Vector m_current_velocity;

		// multi and single frame forces
		Vector m_mf_force;
		Vector m_sf_force;

		// Dampening coefficient
		double m_dampening;

		// Shape (position and size as integers)
		Shape* m_shape_ptr;

		// Position in double form
		Vector m_position;

		// Staticness (if reacts when collided with)
		bool m_is_static;

		// Material (for friction
		Material m_material;
	};
}