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
		bool isStationary() const;

		// Force Accessors
		Vector getAppliedForce();
		void applyMFForce(Vector force);
		void applySFForce(Vector force);
		void clearSFForce();

		// Movement Accessors
		Vector getMovement() const;
		void setMovement(double x_moved, double y_moved);
		void setMovement(Vector movement);

		void addTickMovement(double x_moved, double y_moved);
		void addTickMovement(Vector movement);

		// Time Accessors
		double getTimeAfterTick();
		void setTimeAfterTick(double time);

		// Dampening Accessor
		double getDampening() const;

		// Shape Accessors
		void setShape(Framework::Shape* shape_ptr);

		int getWidth() const;
		int getHeight() const;
		Vector getPosition() const;
		void setPosition(Vector position);
		int getRoundedX() const;
		int getRoundedY() const;

		void move();

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

		// Movement after a single tick
		Vector m_movement;

		// Collision Time (neccessary for checking collision distances)
		// 0 by default, max is tick length
		double m_time_after_tick;

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