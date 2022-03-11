#include "Physics.h"

#include "Vector.h"
#include "RigidBody.h"

#include <cmath>
#include "GridCollisionManager.h"


Framework::Physics::Physics(double time_step, double ppm, double x_damping)
	:TIME_STEP(time_step), PIXELS_PER_METER(ppm)
{
	m_material_manager = nullptr;
	m_material_manager = new MaterialManager();
	m_material_manager->initialize();
}

Framework::Physics::~Physics()
{
	delete m_material_manager;
	m_material_manager = nullptr;
}

double Framework::Physics::getTimeStep() const
{
	return TIME_STEP;
}

double Framework::Physics::getPPM() const
{
	return PIXELS_PER_METER;
}


Framework::Vector Framework::Physics::nextStep(RigidBody* physics_data)
{
	// Classic SUVAT Equations
	Vector distance_moved = getDisplacementAtTime(getTimeStep(), physics_data->getVelocity(), physics_data->getAppliedForce() / physics_data->getMass());

	return distance_moved;

}

double Framework::Physics::getDisplacementAtTime(double time, double axis_velocity, double axis_acceleration)
{
	// Classic s = ut + 0.5at^2
	return (axis_velocity * time + 0.5 * axis_acceleration * pow(time, 2)) * PIXELS_PER_METER;
}

Framework::Vector Framework::Physics::getDisplacementAtTime(double time, Vector velocity, Vector acceleration)
{
	// Classic s = ut + 0.5at^2, but in vector form
	return ((velocity * time) + (acceleration * (0.5 * pow(time, 2)))) * PIXELS_PER_METER;
}

double Framework::Physics::getCoefficientOfRestitution(RigidBody* rigid_body_1, RigidBody* rigid_body_2)
{
	return m_material_manager->getCoefficientOfRestitution(rigid_body_1->getMaterial(), rigid_body_2->getMaterial());
}


void Framework::Physics::applyDampening(RigidBody* data)
{
	if (abs(data->getVelocity().x_value) > 0)
	{
		if (abs(data->getVelocity().x_value) < 0.05)
		{
			data->applySFForce({ data->getMass() * -data->getVelocity().x_value / TIME_STEP, 0 });
		}
		else
		{
			double x_dampening_force = data->getVelocity().x_value * data->getVelocity().x_value * data->getDampening();

			double x_dampening = x_dampening_force / data->getMass() * TIME_STEP;

			if (data->getVelocity().x_value > 0)
			{
				if (x_dampening > data->getVelocity().x_value)
				{
					data->applySFForce({ data->getMass() * -data->getVelocity().x_value / TIME_STEP, 0 });
				}
				else
				{
					data->applySFForce({ -x_dampening_force, 0 });
				}
			}
			else
			{
				if (-x_dampening < data->getVelocity().x_value)
				{
					data->applySFForce({ data->getMass() * -data->getVelocity().x_value / TIME_STEP, 0 });
				}
				else
				{
					data->applySFForce({ x_dampening_force, 0 });
				}
			}
		}	
	}

	if (abs(data->getVelocity().y_value) > 0)
	{
		
		if (abs(data->getVelocity().y_value) < 0.05)
		{
			data->applySFForce({ 0, data->getMass() * -data->getVelocity().y_value / TIME_STEP });
		}
		else
		{
			double y_dampening_force = data->getVelocity().y_value * data->getVelocity().y_value * data->getDampening();

			double y_dampening = y_dampening_force / data->getMass() * TIME_STEP;

			if (data->getVelocity().y_value > 0)
			{
				if (y_dampening > data->getVelocity().y_value)
				{
					data->applySFForce({ 0, data->getMass() * -data->getVelocity().y_value / TIME_STEP });
				}
				else
				{
					data->applySFForce({ 0, -y_dampening_force });
				}
			}
			else
			{
				if (-y_dampening < data->getVelocity().y_value)
				{
					data->applySFForce({ 0, data->getMass() * -data->getVelocity().y_value / TIME_STEP });
				}
				else
				{
					data->applySFForce({ 0, y_dampening_force });
				}
			}
		}
	}
}

double Framework::Physics::getStaticFrictionCoefficient(RigidBody* rigid_body_1, RigidBody* rigid_body_2)
{
	return m_material_manager->getStaticFrictionCoefficient(rigid_body_1->getMaterial(), rigid_body_2->getMaterial());
}

double Framework::Physics::getDynamicFrictionCoefficient(RigidBody* rigid_body_1, RigidBody* rigid_body_2)
{
	return m_material_manager->getDynamicFrictionCoefficient(rigid_body_1->getMaterial(), rigid_body_2->getMaterial());
}

void Framework::Physics::setVelocityAtTime(RigidBody* data, double time)
{
	data->increaseVelocity(data->getAppliedForce() / data->getMass() * time);
}
