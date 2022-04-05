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

        std::pair<double, double> calculateCollisionForces(const RigidBody& r1, const RigidBody& r2, double time_left, int axis) const;

        // Friction
        // TODO: why not just let them access material manager?
        double getStaticFrictionCoefficient(const RigidBody* rigid_body_1, const RigidBody* rigid_body_2) const;
        double getDynamicFrictionCoefficient(const RigidBody* rigid_body_1, const RigidBody* rigid_body_2) const;

    private:
        // --- Data ---
        const MaterialManager m_material_manager;

        // --- Const Data ---
        const double m_time_step;
        const double m_pixels_per_meter;
    };
}
