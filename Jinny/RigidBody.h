#pragma once

#include "Material.h"
#include "Vector.h"
#include "Shape.h"

namespace framework
{
    enum class Material;

    /**
     * Class that contains physics-related data on a rigid body.
     */
    class RigidBody
    {
    public:
        // Constructor
        RigidBody(double mass, double damping_force, Vector max_speed, Shape shape, Material material);

        // Mass Accessors
        double getMass() const;

        // Velocity Accessors
        Vector getVelocity() const;
        void increaseVelocity(Vector additional_velocity);
        bool isStationary() const;

        // Force Accessors
        Vector getAppliedForce();
        void applyMFForce(Vector force);
        void applySFForce(Vector force);
        void clearSFForce();

        // Dampening Accessor
        double getDamping() const;

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
        const double m_mass{ 1 };

        // Current Velocity in meters per second
        Vector m_current_velocity{ 0, 0 };

        // multi and single frame forces
        Vector m_mf_force{ 0, 0 };
        Vector m_sf_force{ 0, 0 };

        // Dampening force
        double m_damping{ 0 };

        // Shape (position and size as integers)
        Shape m_shape;

        // Position in double form
        Vector m_position{ 0, 0 };

        // Staticness (if reacts when collided with)
        bool m_is_static{ false };

        // Material (for friction
        Material m_material{ Material::nullium };

        Vector m_max_speed{ 0, 0 };
    };
}