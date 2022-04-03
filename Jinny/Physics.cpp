#include "Physics.h"

#include "RigidBody.h"

#include <cmath>


framework::Physics::Physics(double time_step, double ppm)
    :m_time_step(time_step), m_pixels_per_meter(ppm), m_material_manager()
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

double framework::Physics::getDisplacementAtTime(double time, double axis_velocity, double axis_acceleration) const
{
    // Classic s = ut + 0.5at^2
    return (axis_velocity * time + 0.5 * axis_acceleration * pow(time, 2)) * m_pixels_per_meter;
}

framework::Vector framework::Physics::getDisplacementAtTime(double time, Vector velocity, Vector acceleration) const
{
    // Classic s = ut + 0.5at^2, but in vector form
    return ((velocity * time) + (acceleration * (0.5 * pow(time, 2)))) * m_pixels_per_meter;
}

double framework::Physics::getCollisionTime(double distance, double velocity_1, double velocity_2, double acceleration_1, double acceleration_2, double max_time) const
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

std::pair<double, double> framework::Physics::calculateDynamicCollisionForces(double a_velocity, double a_mass, double t_velocity, double t_mass, double coeff_restitution, double time_left) const
{
    std::pair<double, double> out;

    double momentum = a_velocity * a_mass + t_velocity * t_mass;

    double right_part = coeff_restitution * (a_velocity - t_velocity);
    double v_a = (momentum - t_mass * right_part) / (t_mass + a_mass);
    double v_t = (momentum + a_mass * right_part) / (t_mass + a_mass);

    out.first = (v_a - a_velocity) * a_mass / time_left;
    out.second = (v_t - t_velocity) * t_mass / time_left;
    return out;
}

double framework::Physics::calculateStaticCollisionForces(double axis_velocity, double axis_force, double mass, double coeff_restitution, double time_left) const
{
    // To stop infinite bouncing (but also let them go naturally in no gravity)
    if (axis_velocity * axis_force > 0 && abs(axis_velocity) < 0.5 * coeff_restitution)
    {
        return (-axis_velocity * mass / time_left);
    }

    return (-axis_velocity * coeff_restitution - axis_velocity) * mass / time_left;
}

double framework::Physics::getCoefficientOfRestitution(RigidBody* rigid_body_1, RigidBody* rigid_body_2) const
{
    return m_material_manager.getCoefficientOfRestitution(rigid_body_1->getMaterial(), rigid_body_2->getMaterial());
}


double framework::Physics::getStaticFrictionCoefficient(RigidBody* rigid_body_1, RigidBody* rigid_body_2) const
{
    return m_material_manager.getStaticFrictionCoefficient(rigid_body_1->getMaterial(), rigid_body_2->getMaterial());
}

double framework::Physics::getDynamicFrictionCoefficient(RigidBody* rigid_body_1, RigidBody* rigid_body_2) const
{
    return m_material_manager.getDynamicFrictionCoefficient(rigid_body_1->getMaterial(), rigid_body_2->getMaterial());
}
