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
		double getXMovement() const;
		double getYMovement() const;

		void setMovement(double x_moved, double y_moved);
		void addTickMovement(double x_moved, double y_moved);
		void setXMovement(double x_moved);
		void setYMovement(double y_moved);

		// Time Accessors
		double getTimeAfterTick();
		void setTimeAfterTick(double time);

		// Dampening Accessor
		double getDampening() const;

		// Shape Accessors
		void setShape(Framework::Shape* shape_ptr);

		int getWidth() const;
		int getHeight() const;
		double getX() const;
		double getY() const;
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
		double m_x_moved;
		double m_y_moved;

		// Collision Time (neccessary for checking collision distances)
		double m_time_after_tick;

		// multi and single frame forces
		Vector m_mf_force;
		Vector m_sf_force;

		// Dampening coefficient
		double m_dampening;

		// Shape
		Shape* m_rigid_body_shape_ptr;
		double m_exact_x;
		double m_exact_y;

		// Staticness (if reacts when collided with)
		bool m_is_static;

		// Materials
		Material m_material;
	};
}