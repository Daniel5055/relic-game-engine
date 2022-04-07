#pragma once

#include <map>
#include <vector>

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

        std::vector<std::pair<int, int>> getTickCollisions();

        // Physics engine specific functions
        void virtual addRigidBody(int object_id, framework::RigidBody* rigid_body);

    protected:

        // Framework data
        const framework::Physics& f_physics;

        // Rigidbody data
        std::map<int, framework::RigidBody*> m_rigid_bodies;

        void registerCollision(int object_1, int object_2);
        void restartTick();

    private:
        std::vector <std::pair<int, int>> m_accumulated_tick_collisions;


    };
}
