#pragma once

#include <map>
#include <vector>

#include "Identifier.h"

// Declaring used classes
namespace framework
{
    class Physics;
    class RigidBody;
}

namespace relic
{
    /**
     * Base class for physics engine to be run by the physics system.
     * These classes are responsible for how the physics are run.
     */
    class PhysicsEngine
    {
    public:
        virtual ~PhysicsEngine() = default;
        // Constructor
        explicit PhysicsEngine(const framework::Physics& physics);

        // Updating
        void virtual update() = 0;

        std::vector<std::pair<Identifier, Identifier>> getTickCollisions();

        // Physics engine specific function
        void virtual addRigidBody(const Identifier& object_id, framework::RigidBody* rigid_body);

        void removeRigidBody(const Identifier& object_id);

    protected:

        // Framework data
        const framework::Physics& f_physics;

        // Rigidbody data
        std::map<Identifier, framework::RigidBody*> m_rigid_bodies;

        void registerCollision(const Identifier& object_1, const Identifier& object_2);
        void restartTick();

    private:
        std::vector <std::pair<Identifier, Identifier>> m_accumulated_tick_collisions;


    };
}
