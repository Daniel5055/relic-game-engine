#pragma once

#include "Vector.h"
#include "Shape.h"
#include "ExactDecimal.h"

namespace Framework
{
	enum class Material;

	class RigidBody
	{
	public:
		// Constructor
		RigidBody(double mass, double m_dampening);

		// Mass Accessors
		double getMass() const;
		void setMass(double mass);

		// Velocity Accessors
		Vector getVelocity();
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
		eDec getXMovement() const;
		eDec getYMovement() const;

		void setMovement(eDec x_moved, eDec y_moved);
		void addTickMovement(eDec x_moved, eDec y_moved);
		void setXMovement(eDec x_moved);
		void setYMovement(eDec y_moved);

		// Time Accessors
		double getTimeAfterTick();
		void setTimeAfterTick(double time);

		// Dampening Accessor
		double getDampening() const;

		// Shape Accessors
		int getWidth() const;
		int getHeight() const;
		eDec getX() const;
		eDec getY() const;
		void setX(int x);
		void setY(int y);
		int getRoundedX() const;
		int getRoundedY() const;

		void move();

		// Static accessor
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
		eDec m_x_moved;
		eDec m_y_moved;

		// Collision Time (neccessary for checking collision distances)
		double m_time_after_tick;

		// multi and single frame forces
		Vector m_mf_force;
		Vector m_sf_force;

		// Dampening coefficient
		double m_dampening;

		// Shape
		Shape* m_rigid_body_shape_ptr;
		eDec m_exact_x;
		eDec m_exact_y;

		// Staticness (if reacts when collided with)
		bool m_is_static;

		// Materials
		Material m_material;
	};
}