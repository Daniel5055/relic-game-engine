#pragma once

#include "Vector.h"
#include <utility>

#include "MaterialManager.h"

namespace framework
{
    // Class definitions
    class RigidBody;

    /**
     * A class for performing general physics calculations.
     */
    class Physics
    {
    public:
        // Constructor
        explicit Physics(double time_step, double ppm);

        // Get consts
        double getTimeStep() const;
        double getPPM() const;

        // For calculating collision positions
        double getDisplacementAtTime(double time, double axis_velocity, double axis_acceleration) const;
        Vector getDisplacementAtTime(double time, Vector velocity, Vector acceleration) const;

        // For calculating collision time and forces
        double getCollisionTime(double distance, double velocity_1, double velocity_2, double acceleration_1,
                                double acceleration_2, double max_time) const;

        std::pair<double, double> calculateDynamicCollisionForces(double a_velocity, double a_mass, double t_velocity,
                                                                  double t_mass, double coeff_restitution,
                                                                  double time_left) const;
        double calculateStaticCollisionForces(double axis_velocity, double axis_force, double mass,
                                              double coeff_restitution, double time_left) const;

        // For getting the coefficient of restitution
        double getCoefficientOfRestitution(RigidBody* rigid_body_1, RigidBody* rigid_body_2) const;

        // Friction
        // TODO: why not just let them access material manager?
        double getStaticFrictionCoefficient(RigidBody* rigid_body_1, RigidBody* rigid_body_2) const;
        double getDynamicFrictionCoefficient(RigidBody* rigid_body_1, RigidBody* rigid_body_2) const;

    private:
        // --- Data ---
        const MaterialManager m_material_manager;

        // --- Const Data ---
        const double m_time_step;
        const double m_pixels_per_meter;
    };
}
