#pragma once

#include <queue>

#include "PhysicsEngine.h"

#include "Vector.h"


namespace relic
{
    /**
     * Physics engine that handles grid collisions with grid rigidbodies.
     * Handles collisions, friction, and damping
     * Bodies cannot rotate in a grid collision system and all bodies are assumed to be rectangular
     */
    class GridPhysicsEngine final :
        public PhysicsEngine
    {
    public:

        // Constructor
        explicit GridPhysicsEngine(const framework::Physics& physics);

        // Updating
        void update() override;

        void addRigidBody(const Identifier& object_id, framework::RigidBody* rigid_body) override;

    private:

        const double m_acceleration_due_to_gravity;

        std::map<std::pair<Identifier, Identifier>, bool> m_legal_clippings;

        // For applying damping on objects with damping
        void applyDamping();
        void moveBodies(double time);

        // Struct used to store basic data on "presence" of a body
        struct InfluenceRectangle
        {
            // Position in top left corner
            framework::Vector position;

            // Size 
            framework::Vector size;
        };

        // For calculating the influence rects of each rigidbody
        std::map<Identifier, InfluenceRectangle> calculateInfluenceRects(double time_passed);

        // For making corrections from clipping
        bool correctClippings(const Identifier& id1, const Identifier& id2);

        // For checking if influence rects intersect
        bool doesIntersect(const InfluenceRectangle& r1, const InfluenceRectangle& r2);

        // Contains data of a collision
        struct Collision
        {
            double time;
            int axis;

            Identifier body_ids[2];
            framework::Vector applying_forces;
        };

        // For finding collisions using influence rects
        std::queue<Collision> findCollisions(const std::map<Identifier, InfluenceRectangle>& influence_rects, double time_passed);

        // For calculating and applying forces in a collision
        void calculateCollision(Collision& collision, double time_passed);

        // For calculating friction caused by a collision
        void calculateFriction(Collision& collision, std::map<Identifier, framework::Vector>& friction_applied, double time_passed);
    };
}

