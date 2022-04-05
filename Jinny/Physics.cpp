#include "Physics.h"

#include "RigidBody.h"

#include <cmath>


framework::Physics::Physics(double time_step, double ppm)
    : m_time_step(time_step), m_pixels_per_meter(ppm)
{
}

double framework::Physics::getTimeStep() const
{
    return m_time_step;
}

double framework::Physics::getPPM() const
{
    return m_pixels_per_meter;
}

double framework::Physics::getDisplacementAtTime(const double time, const double axis_velocity, const double axis_acceleration) const
{
    // Classic s = ut + 0.5at^2
    return (axis_velocity * time + 0.5 * axis_acceleration * pow(time, 2)) * m_pixels_per_meter;
}

framework::Vector framework::Physics::getDisplacementAtTime(const double time, const Vector velocity, const Vector acceleration) const
{
    // Classic s = ut + 0.5at^2, but in vector form
    return ((velocity * time) + (acceleration * (0.5 * pow(time, 2)))) * m_pixels_per_meter;
}

double framework::Physics::getCollisionTime(const double distance, const double velocity_1, const double velocity_2, const double acceleration_1, const double acceleration_2, const double max_time) const
{
    // variable useful for some stuff here
    double time = -1;

    // Distance refers to target pos - arrow pos (can be negative (maybe i should say displacement))
    if ((acceleration_1 == acceleration_2))
    {
        // Physics formula for time which two colliding objects will hit using suvat and two objects
        time = (distance / m_pixels_per_meter) / (velocity_1 - velocity_2);

        if (time > 0)
        {
            if (time > max_time)
            {
                // Because then axis_acceleration_2 must also be zero
                if (acceleration_1 != 0)
                {
                    // Then redo calculations with max_time
                    double max_distance = double(velocity_2 * max_time + 0.5 * acceleration_2 * pow(max_time, 2) + distance / m_pixels_per_meter);

                    double discriminant = pow(velocity_1, 2) + 2 * (max_distance) * (acceleration_1);

                    if (discriminant < 0)
                    {
                        return -1;
                    }

                    double b_negative = (-velocity_1);
                    double a = (acceleration_1);

                    time = (b_negative - sqrt(discriminant)) / a;

                    // Determining correct time (smallest non negative collision)
                    if (time >= 0)
                    {
                        // Check other solution in case
                        double other_time = (b_negative + sqrt(discriminant)) / a;
                        if (other_time < time && other_time > 0)
                        {
                            return other_time;
                        }
                        else
                        {
                            return time;
                        }
                    }
                    else
                    {
                        return (b_negative + sqrt(discriminant)) / a;
                    }
                }
                else if (velocity_1 == velocity_2)
                {
                    return -1;

                }
                else
                {
                    // what?
                    return ((distance / m_pixels_per_meter + velocity_2 * max_time) / (velocity_1));
                }

            }
            else
            {
                return time;
            }
        }
        else if (time == 0)
        {
            if (velocity_1 > velocity_2)
            {
                return time;
            }
            else
            {
                return -1;
            }
        }
        else
        {
            return -1;

            // Not sure about this code so I will ignore this
            if (acceleration_1 != 0)
            {
                // Then redo calculations with max_time
                double max_distance = double(velocity_2 * max_time + 0.5 * acceleration_2 * pow(max_time, 2) + distance / m_pixels_per_meter);

                double discriminant = pow(velocity_1, 2) + 2 * (max_distance) * (acceleration_1);

                if (discriminant < 0)
                {
                    return -1;
                }

                double b_negative = (-velocity_1);
                double a = (acceleration_1);

                time = (b_negative - sqrt(discriminant)) / a;

                // Determining correct time (smallest non negative collision)
                if (time >= 0)
                {
                    // Check other solution in case
                    double other_time = (b_negative + sqrt(discriminant)) / a;;
                    if (other_time < time && other_time > 0)
                    {
                        return other_time;
                    }
                    else
                    {
                        return time;
                    }
                }
                else
                {
                    return (b_negative + sqrt(discriminant)) / a;
                }
            }
            else
            {
                return ((distance / m_pixels_per_meter + velocity_2 * max_time) / (velocity_1));
            }
        }

    }

    // For cases where they are already in contact
    else if (distance == 0)
    {
        if (velocity_1 > velocity_2)
        {
            return 0;
        }
        else if (abs(velocity_1 - velocity_2) < 0.000000001)
        {
            // equal to zero
            if (acceleration_1 > acceleration_2)
            {
                return 0;
            }
            else
            {
                // I dont understand any of these max time calculatations?
                double max_distance = double(velocity_2 * max_time + 0.5 * acceleration_2 * pow(max_time, 2));

                double discriminant = pow(velocity_1, 2) + 2 * (max_distance) * (acceleration_1);

                if (discriminant < 0)
                {
                    return -1;
                }

                double b_negative = (-velocity_1);
                double a = (acceleration_1);

                time = (b_negative - sqrt(discriminant)) / a;

                // Determining correct time (smallest non negative collision)
                if (time >= 0)
                {
                    // Check other solution in case
                    double other_time = (b_negative + sqrt(discriminant)) / a;;
                    if (other_time < time && other_time > 0)
                    {
                        return other_time;
                    }
                    else
                    {
                        return time;
                    }
                }
                else
                {
                    return (b_negative + sqrt(discriminant)) / a;
                }

            }
        }
        else
        {
            return -1;
        }
    }

    // Advanced suvat equation using quadratic formula

    double discriminant = pow(velocity_1 - velocity_2, 2) + 2 * (distance / m_pixels_per_meter) * (acceleration_1 - acceleration_2);

    if (discriminant < 0)
    {
        double max_distance = double(velocity_2 * max_time + 0.5 * acceleration_2 * pow(max_time, 2));
        discriminant = pow(velocity_1, 2) + 2 * (distance / m_pixels_per_meter + max_distance) * acceleration_1;

        if (discriminant < 0)
        {
            return -1;
        }

        time = (-velocity_1 - sqrt(discriminant)) / acceleration_1;

        // Same check as before for determining correct collision
        if (time >= 0)
        {
            // Check other solution in case
            double other_time = (-velocity_1 + sqrt(discriminant)) / acceleration_1;
            if (other_time < time && other_time > 0)
            {
                return other_time;
            }
            else
            {
                return time;
            }
        }
        else
        {
            return (-velocity_1 + sqrt(discriminant)) / acceleration_1;
        }
    }

    double b_negative = (velocity_2 - velocity_1);
    double a = (acceleration_1 - acceleration_2);

    time = (b_negative - sqrt(discriminant)) / a;

    // Determining correct time (smallest non negative collision)
    if (time >= 0)
    {
        // Check other solution in case
        double other_time = (b_negative + sqrt(discriminant)) / a;
        if (other_time < time && other_time > 0)
        {
            // Check if time is not greater than max
            if (time > max_time)
            {
                double max_distance = double(velocity_2 * max_time + 0.5 * acceleration_2 * pow(max_time, 2));
                discriminant = pow(velocity_1, 2) + 2 * (distance / m_pixels_per_meter + max_distance) * acceleration_1;

                // Is this check neccessary? AAAAAAAAAAAAAAAAAAAA
                if (discriminant < 0)
                {
                    return -1;
                }

                time = (-velocity_1 - sqrt(discriminant)) / acceleration_1;

                // Same check as before for determining correct collision
                if (time >= 0)
                {
                    // Check other solution in case
                    other_time = (b_negative + sqrt(discriminant)) / a;
                    if (other_time < time && other_time > 0)
                    {
                        return other_time;
                    }
                    else
                    {
                        return time;
                    }
                }
                else
                {
                    return (-velocity_1 + sqrt(discriminant)) / acceleration_1;
                }
            }
            else
            {
                return time;
            }

        }

        // Check if time is not greater than max
        if (time > max_time)
        {
            double max_distance = double(velocity_2 * max_time + 0.5 * acceleration_2 * pow(max_time, 2));
            discriminant = pow(velocity_1, 2) + 2 * (distance / m_pixels_per_meter + max_distance) * acceleration_1;

            // Is this check neccessary? AAAAAAAAAAAAAAAAAAAA
            if (discriminant < 0)
            {
                return -1;
            }

            time = (-velocity_1 - sqrt(discriminant)) / acceleration_1;

            // Same check as before for determining correct collision
            if (time >= 0)
            {
                // Check other solution in case
                double other_time = (-velocity_1 + sqrt(discriminant)) / acceleration_1;
                if (other_time < time && other_time > 0)
                {
                    return other_time;
                }
                else
                {
                    return time;
                }
            }
            else
            {
                return (-velocity_1 + sqrt(discriminant)) / acceleration_1;
            }
        }
        else
        {
            return time;
        }
    }
    else
    {
        time = (b_negative + sqrt(discriminant)) / a;

        // Check if time is not greater than max
        if (time > max_time)
        {
            double max_distance = double(velocity_2 * max_time + 0.5 * acceleration_2 * pow(max_time, 2));
            discriminant = pow(velocity_1, 2) + 2 * (distance / m_pixels_per_meter + max_distance) * acceleration_1;

            // Is this check neccessary? AAAAAAAAAAAAAAAAAAAA
            if (discriminant < 0)
            {
                return -1;
            }

            time = (-velocity_1 - sqrt(discriminant)) / acceleration_1;

            // Same check as before for determining correct collision
            if (time >= 0)
            {
                // Check other solution in case
                double other_time = (-velocity_1 + sqrt(discriminant)) / acceleration_1;
                if (other_time < time && other_time > 0)
                {
                    return other_time;
                }
                else
                {
                    return time;
                }
            }
            else
            {
                return (-velocity_1 + sqrt(discriminant)) / acceleration_1;
            }
        }
        else
        {
            return time;
        }
    }

    // With regards to checking, I am not sure how many of the possibilities I have created are possible
}

std::pair<double, double> framework::Physics::calculateCollisionForces(const RigidBody& r1, const RigidBody& r2, const double time_left, const int axis) const
{
    std::pair<double, double> out;

    const double momentum = r1.getVelocity()[axis] * r1.getMass() + r2.getVelocity()[axis] * r2.getMass();

    const double right_part = m_material_manager.getCoefficientOfRestitution(r1.getMaterial(), r2.getMaterial()) * (r1.getVelocity()[axis] - r2.getVelocity()[axis]);
    const double v_1 = (momentum - r2.getMass() * right_part) / (r2.getMass() + r1.getMass());
    const double v_2 = (momentum + r1.getMass() * right_part) / (r2.getMass() + r1.getMass());

    // TODO: Not gonna lie, this could be done better
    // Handling static and non static collisions
    if (r1.isStatic())
    {
        out.first = (-r1.getVelocity()[axis]) * r1.getMass() / time_left;
    }
    else
    {
        if (r2.isStatic())
        {
            if (r1.getVelocity()[axis] * r1.getAppliedForce()[axis] > 0 &&
                abs(r1.getVelocity()[axis]) < 0.5 * m_material_manager.getCoefficientOfRestitution(r1.getMaterial(), r2.getMaterial()))
            {
                out.first = (-r1.getVelocity()[axis]) * r1.getMass() / time_left;
            }
            else
            {
                out.first = (-r1.getVelocity()[axis] * m_material_manager.getCoefficientOfRestitution(r1.getMaterial(), r2.getMaterial()) - r1.getVelocity()[axis]) * r1.getMass() / time_left;
            }
        }
        else
        {
            out.first = (v_1 - r1.getVelocity()[axis]) * r1.getMass() / time_left;
        }
    }

    if (r2.isStatic())
    {
        out.second = (-r2.getVelocity()[axis]) * r2.getMass() / time_left;
    }
    else
    {
        if (r1.isStatic())
        {
            if (r2.getVelocity()[axis] * r2.getAppliedForce()[axis] > 0 &&
                abs(r2.getVelocity()[axis]) < 0.5 * m_material_manager.getCoefficientOfRestitution(r1.getMaterial(), r2.getMaterial()))
            {
                out.second = (-r2.getVelocity()[axis]) * r2.getMass() / time_left;
            }
            else
            {
                out.second = (-r2.getVelocity()[axis] * m_material_manager.getCoefficientOfRestitution(r1.getMaterial(), r2.getMaterial()) - r2.getVelocity()[axis]) * r2.getMass() / time_left;
            }
        }
        else
        {
            out.second = (v_2 - r2.getVelocity()[axis]) * r2.getMass() / time_left;
        }
    }

    return out;
}

double framework::Physics::getStaticFrictionCoefficient(const RigidBody* rigid_body_1, const RigidBody* rigid_body_2) const
{
    return m_material_manager.getStaticFrictionCoefficient(rigid_body_1->getMaterial(), rigid_body_2->getMaterial());
}

double framework::Physics::getDynamicFrictionCoefficient(const RigidBody* rigid_body_1, const RigidBody* rigid_body_2) const
{
    return m_material_manager.getDynamicFrictionCoefficient(rigid_body_1->getMaterial(), rigid_body_2->getMaterial());
}
