#pragma once

#include <map>

// Declaring used classes
namespace Framework
{
    class Physics;
    class RigidBody;
}

namespace Jinny
{
    /**
     * Base class for physics engine to be run by the physics system.
     * These classes are responsible for how the physics are run.
     */
    class PhysicsEngine
    {
    public:
        // Constructor
        PhysicsEngine();

        // Initialisation
        void virtual initialise(const Framework::Physics* physics_ptr);

        // Upating
        void virtual update() = 0;

        // Closing
        void virtual close();

        // Physics engine specific functions
        void virtual addRigidBody(int object_id, Framework::RigidBody* rigid_body);

    protected:
        
        // Framework data
        const Framework::Physics* f_physics;

        // Rigidbody data
        std::map<int, Framework::RigidBody*> m_rigid_bodies;
    };
}
