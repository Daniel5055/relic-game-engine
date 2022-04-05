#include "GridPhysicsEngine.h"

#include "RigidBody.h"
#include "Physics.h"


relic::GridPhysicsEngine::GridPhysicsEngine(const framework::Physics& physics)
    : PhysicsEngine(physics), m_acceleration_due_to_gravity(9.81)
{
}

void relic::GridPhysicsEngine::update()
{
    double time_passed = 0;

    applyDamping();

    while (true)
    {
        // Define map containing force applied in friction
        std::map<int, framework::Vector> friction_applied;

        // Find influence rects
        std::map<int, InfluenceRectangle> influence_rects = calculateInfluenceRects(time_passed);

        // Calculate collisions from influence rects
        std::queue<Collision> collisions = findCollisions(influence_rects, time_passed);

        // If collisions empty then break else if time is -1 then issue
        if (collisions.empty())
        {
            break;
        }
        if (collisions.front().time == -1)
        {
            continue;
        }

        // Move objects to most recent collision time
        moveBodies(collisions.front().time);
        time_passed += collisions.front().time;

        // Iterate through collisions
        while (!collisions.empty())
        {
            calculateCollision(collisions.front(), time_passed);
            calculateFriction(collisions.front(), friction_applied, time_passed);
            collisions.pop();
        }

        // Iterate through friction forces applied and apply the forces finally
        for (auto it = friction_applied.begin(); it != friction_applied.end(); ++it)
        {
            m_rigid_bodies[it->first]->applySFForce(it->second);
        }
    }

    // Move the bodies
    moveBodies(f_physics.getTimeStep() - time_passed);

    // clear single tick forces
    for (auto it = m_rigid_bodies.begin(); it != m_rigid_bodies.end(); ++it)
    {
        it->second->clearSFForce();
    }
}

void relic::GridPhysicsEngine::addRigidBody(int object_id, framework::RigidBody* rigid_body)
{
    // Apply gravity
    if (!rigid_body->isStatic())
    {
        rigid_body->applyMFForce({ 0, m_acceleration_due_to_gravity * rigid_body->getMass() });
    }
    PhysicsEngine::addRigidBody(object_id, rigid_body);
}

void relic::GridPhysicsEngine::applyDamping()
{
    // Iterate through rigid bodies
    for (const auto& body : m_rigid_bodies)
    {
        if (body.second->getDamping() > 0)
        {
            for (const int axis : {0, 1})
            {
                // Max force to reduce velocity to zero
                const double max_force = abs(body.second->getVelocity()[axis]) * body.second->getMass() / (f_physics.getTimeStep());

                // Make sure velocity is greater than zero
                if (max_force > 0)
                {
                    framework::Vector damping_force = { 0, 0 };

                    damping_force[axis] = body.second->getDamping() * body.second->getMass() / (f_physics.getTimeStep());

                    // Make sure damping force is not bigger than max force
                    if (max_force < damping_force[axis])
                    {
                        damping_force[axis] = max_force;
                    }

                    // Apply damping force in right direction
                    if (body.second->getVelocity()[axis] > 0)
                    {
                        body.second->applySFForce(damping_force * -1);
                    }
                    else
                    {
                        body.second->applySFForce(damping_force);
                    }
                }
            }
        }
    }
}

void relic::GridPhysicsEngine::moveBodies(double time)
{
    // Move objects to new positon in duration of time
    for (auto it = m_rigid_bodies.begin(); it != m_rigid_bodies.end(); it++)
    {
        it->second->move(f_physics.getDisplacementAtTime(time, it->second->getVelocity(),
            it->second->getAppliedForce() / it->second->getMass()));
        it->second->increaseVelocity(it->second->getAppliedForce() * time / it->second->getMass());
    }
}

bool relic::GridPhysicsEngine::correctClippings(const int id1, const int id2)
{
    // Check if bodies are clipping

    // Define influence rects of objects without motion
    InfluenceRectangle r[2];
    r[0] = { m_rigid_bodies[id1]->getPosition(), m_rigid_bodies[id1]->getSize() };
    r[1] = { m_rigid_bodies[id2]->getPosition(), m_rigid_bodies[id2]->getSize() };

    // Check if they clip
    if (doesIntersect(r[0], r[1]))
    {
        double smallest_distance = 1000000;
        int closest_axis = -1;
        int left_most = -1;

        // Iterate through axis and rigid body to find the smallest distance between edges
        for (int axis : {0, 1})
        {
            for (int r_i : {0, 1})
            {
                // Calculate the distance between the two edges
                double distance = r[r_i].position[axis] + r[r_i].size[axis] - r[1 - r_i].position[axis];

                if (distance < smallest_distance)
                {
                    smallest_distance = distance;
                    closest_axis = axis;
                    left_most = r_i;
                }
            }
        }

        // Lambda functions for what type of clipping correction occurs
        auto moveOne = [&](int moved_body_id, int still_body_id, int moved_rel_id)
        {
            framework::Vector new_position = m_rigid_bodies[moved_body_id]->getPosition();

            if (moved_rel_id == left_most)
            {
                new_position[closest_axis] = r[1 - left_most].position[closest_axis] - r[left_most].size[closest_axis];
            }
            else
            {
                new_position[closest_axis] = r[left_most].position[closest_axis] + r[left_most].size[closest_axis];

            }

            // Move to new position
            m_rigid_bodies[moved_body_id]->setPosition(new_position);
        };

        auto moveBoth = [&](int body_id_1, int body_id_2)
        {
            // Calculate the movement of the bodies
            framework::Vector movement = { 0, 0 };
            movement[closest_axis] = smallest_distance / 2;
            if (left_most == 0)
            {
                m_rigid_bodies[body_id_1]->move(movement * -1);
                m_rigid_bodies[body_id_2]->move(movement);
            }
            else
            {
                m_rigid_bodies[body_id_2]->move(movement * -1);
                m_rigid_bodies[body_id_1]->move(movement);
            }
        };

        if (m_rigid_bodies[id1]->isStatic() && m_rigid_bodies[id2]->isStatic())
        {
            // Only move the static body in motion else move both equally
            // TODO: could check stationary across single axis
            if ((m_rigid_bodies[id1]->isStationary() && m_rigid_bodies[id2]->isStationary())
                || (!m_rigid_bodies[id1]->isStationary() && !m_rigid_bodies[id2]->isStationary()))
            {
                moveBoth(id1, id2);
            }
            else
            {
                if (m_rigid_bodies[id1]->isStationary())
                {
                    moveOne(id2, id1, 1);
                }
                else
                {
                    moveOne(id1, id2, 0);
                }
            }
        }
        else if (m_rigid_bodies[id1]->isStatic() || m_rigid_bodies[id2]->isStatic())
        {
            // Only move the non static body if one is static
            if (m_rigid_bodies[id1]->isStatic())
            {
                moveOne(id2, id1, 1);
            }
            else
            {
                moveOne(id1, id2, 0);
            }
        }
        else
        {
            moveBoth(id1, id2);
        }
    }
    else
    {
        return false;
    }

    return true;
}

std::map<int, relic::GridPhysicsEngine::InfluenceRectangle> relic::GridPhysicsEngine::calculateInfluenceRects(double time_passed)
{
    // Create output map
    std::map<int, InfluenceRectangle> influence_rects = std::map<int, InfluenceRectangle>();

    // Iterate through bodies
    for (const auto body : m_rigid_bodies)
    {
        // Initialise default position and size
        framework::Vector size = framework::Vector(body.second->getWidth(), body.second->getHeight());
        framework::Vector position = body.second->getPosition();

        // For each axis
        for (int axis : {0, 1})
        {
            // Calculate the displacement of object across axis and show that in the position and size
            double displacement = f_physics.getDisplacementAtTime(f_physics.getTimeStep() - time_passed,
                body.second->getVelocity()[axis],
                body.second->getAppliedForce()[axis] / body.second->getMass());

            if (displacement < 0)
            {
                position[axis] += displacement;
            }

            size[axis] += abs(displacement);
        }

        // Add to map of influence rects
        influence_rects.insert({ body.first, {position, size} });

    }
    return influence_rects;
}

bool relic::GridPhysicsEngine::doesIntersect(const InfluenceRectangle& r1, const InfluenceRectangle& r2)
{
    // Check if intersects 
    for (const int axis : {0, 1})
    {
        if (r1.position[axis] >= r2.position[axis] + r2.size[axis] ||
            r2.position[axis] >= r1.position[axis] + r1.size[axis])
        {
            return false;
        }
    }
    return true;
}

std::queue<relic::GridPhysicsEngine::Collision> relic::GridPhysicsEngine::findCollisions(const std::map<int, InfluenceRectangle>& influence_rects, double time_passed)
{
    // Create output queue of collisions
    std::queue<Collision> collisions;

    // Iterate between all objects to find collisions
    for (auto it1 = influence_rects.begin(); it1 != influence_rects.end(); it1++)
    {
        // TODO: A bit janky 
        auto it2 = influence_rects.begin();
        int dist = std::distance(it2, it1);
        for (int i = 0; i < dist; i++)
        {
            ++it2;
        }

        for (++it2; it2 != influence_rects.end(); ++it2)
        {
            // Check if possible collision
            if (doesIntersect(it1->second, it2->second))
            {
                // Correct clippings, returns true if clipping occurred, in which case need to recalculate stuff
                if (correctClippings(it1->first, it2->first))
                {
                    // Create fake collision to signify influence rects must be calculated
                    auto problem = std::queue<Collision>();
                    problem.push({ -1 });

                    return problem;
                }

                // Get time of collision
                double collision_times[2] = { 0, 0 };
                for (const int axis : {0, 1})
                {
                    // Calculate distance between bodies along axis
                    double distance = 0;
                    if (m_rigid_bodies[it2->first]->getPosition()[axis] < m_rigid_bodies[it1->first]->getPosition()[axis])
                    {
                        distance = m_rigid_bodies[it1->first]->getPosition()[axis] - m_rigid_bodies[it2->first]->getPosition()[axis] - m_rigid_bodies[it2->first]->getSize()[axis];
                    }
                    else
                    {
                        distance = m_rigid_bodies[it2->first]->getPosition()[axis] - m_rigid_bodies[it1->first]->getPosition()[axis] - m_rigid_bodies[it1->first]->getSize()[axis];
                    }

                    // If less then zero then next
                    if (distance < 0)
                    {
                        collision_times[axis] = -1;
                        continue;
                    }

                    // Calculate the collision time, with the first body being the one with the smallest axis coord
                    if (m_rigid_bodies[it1->first]->getPosition()[axis] < m_rigid_bodies[it2->first]->getPosition()[axis])
                    {
                        collision_times[axis] = f_physics.getCollisionTime(distance, m_rigid_bodies[it1->first]->getVelocity()[axis], m_rigid_bodies[it2->first]->getVelocity()[axis],
                            m_rigid_bodies[it1->first]->getAppliedForce()[axis] / m_rigid_bodies[it1->first]->getMass(),
                            m_rigid_bodies[it2->first]->getAppliedForce()[axis] / m_rigid_bodies[it2->first]->getMass(), f_physics.getTimeStep() - time_passed);
                    }
                    else
                    {
                        collision_times[axis] = f_physics.getCollisionTime(distance, m_rigid_bodies[it2->first]->getVelocity()[axis], m_rigid_bodies[it1->first]->getVelocity()[axis],
                            m_rigid_bodies[it2->first]->getAppliedForce()[axis] / m_rigid_bodies[it2->first]->getMass(),
                            m_rigid_bodies[it1->first]->getAppliedForce()[axis] / m_rigid_bodies[it1->first]->getMass(), f_physics.getTimeStep() - time_passed);
                    }

                    // Make sure return time is within limit (TODO: maybe should add this in function instead)
                    if (collision_times[axis] > f_physics.getTimeStep() - time_passed)
                    {
                        collision_times[axis] = -1;
                    }
                }

                // Check if objects are touching at time
                int smallest = 0;
                int largest = 1;

                // Start with smallest collision
                if (collision_times[0] > collision_times[1])
                {
                    smallest = 1;
                    largest = 0;
                }

                for (const int axis : {smallest, largest})
                {
                    if (collision_times[axis] >= 0)
                    {
                        const double displacement1 = f_physics.getDisplacementAtTime(collision_times[axis], m_rigid_bodies[it1->first]->getVelocity()[1 - axis],
                                                                                     m_rigid_bodies[it1->first]->getAppliedForce()[1 - axis] / m_rigid_bodies[it1->first]->getMass());
                        const double displacement2 = f_physics.getDisplacementAtTime(collision_times[axis], m_rigid_bodies[it2->first]->getVelocity()[1 - axis],
                                                                                     m_rigid_bodies[it2->first]->getAppliedForce()[1 - axis] / m_rigid_bodies[it2->first]->getMass());

                        // Check if on same level (pretty sure this math is correct)
                        // +1 to stop corner problems
                        if (displacement1 + it1->second.position[1 - axis] <= displacement2 + it2->second.position[1 - axis] + it2->second.size[1 - axis] + 1 ||
                            displacement2 + it2->second.position[1 - axis] <= displacement1 + it1->second.position[1 - axis] + it1->second.size[1 - axis] + 1)
                        {
                            if (!collisions.empty())
                            {
                                if (collisions.front().time > collision_times[axis])
                                {
                                    collisions = std::queue<Collision>();
                                    collisions.push({ collision_times[axis], axis, {it1->first, it2->first} });
                                }
                                else if (collisions.front().time == collision_times[axis])
                                {
                                    collisions.push({ collision_times[axis], axis, {it1->first, it2->first} });
                                }
                            }
                            else
                            {
                                collisions.push({ collision_times[axis], axis, {it1->first, it2->first} });
                            }

                            // Found collision along axis so no need to check other axis
                            break;
                        }
                    }
                }
            }
        }
    }
    return collisions;
}

void relic::GridPhysicsEngine::calculateCollision(Collision& collision, const double time_passed)
{
    framework::Vector normal1 = m_rigid_bodies[collision.body_ids[0]]->getAppliedForce() * -1;
    normal1[1 - collision.axis] = 0;
    framework::Vector normal2 = m_rigid_bodies[collision.body_ids[1]]->getAppliedForce() * -1;
    normal2[1 - collision.axis] = 0;

    // Apply normal depending on staticness
    collision.applying_forces = { 0, 0 };
    if (m_rigid_bodies[collision.body_ids[0]]->isStatic())
    {
        collision.applying_forces[0] = normal1[collision.axis];
        m_rigid_bodies[collision.body_ids[0]]->applySFForce(normal1);
    }
    else
    {
        collision.applying_forces[0] = normal1[collision.axis] + normal2[collision.axis] * -1;
        m_rigid_bodies[collision.body_ids[0]]->applySFForce(normal1 + normal2 * -1);
    }

    if (m_rigid_bodies[collision.body_ids[1]]->isStatic())
    {
        collision.applying_forces[1] = normal2[collision.axis];
        m_rigid_bodies[collision.body_ids[1]]->applySFForce(normal2);
    }
    else
    {
        collision.applying_forces[1] = normal2[collision.axis] + normal1[collision.axis] * -1;
        m_rigid_bodies[collision.body_ids[1]]->applySFForce(normal2 + normal1 * -1);
    }

    // Apply collision forces
    const std::pair<double, double> collision_forces = f_physics.calculateCollisionForces(*m_rigid_bodies[collision.body_ids[0]], *m_rigid_bodies[collision.body_ids[1]],
        f_physics.getTimeStep() - time_passed, collision.axis);

    auto collision_force1 = framework::Vector();
    collision_force1[collision.axis] = collision_forces.first;
    auto collision_force2 = framework::Vector();
    collision_force2[collision.axis] = collision_forces.second;

    collision.applying_forces[0] += collision_forces.first;
    collision.applying_forces[1] += collision_forces.second;


    m_rigid_bodies[collision.body_ids[0]]->increaseVelocity(collision_force1 / m_rigid_bodies[collision.body_ids[0]]->getMass() * (f_physics.getTimeStep() - time_passed));
    m_rigid_bodies[collision.body_ids[1]]->increaseVelocity(collision_force2 / m_rigid_bodies[collision.body_ids[1]]->getMass() * (f_physics.getTimeStep() - time_passed));
}

void relic::GridPhysicsEngine::calculateFriction(Collision& collision, std::map<int, framework::Vector>& friction_applied, const double time_passed)
{

    // Calculate friction
    for (const int r : {0, 1})
    {
        // Check if rigid body exists in friction map
        if (!friction_applied.count(collision.body_ids[r]))
        {
            friction_applied.insert({ collision.body_ids[r], {0, 0} });
        }

        framework::Vector friction = { 0, 0 };

        // Check for static friction
        if (m_rigid_bodies[collision.body_ids[0]]->getVelocity()[1 - collision.axis] == m_rigid_bodies[collision.body_ids[1]]->getVelocity()[1 - collision.axis])
        {
            friction[1 - collision.axis] = abs(collision.applying_forces[r]) *
                f_physics.getStaticFrictionCoefficient(m_rigid_bodies[collision.body_ids[0]], m_rigid_bodies[collision.body_ids[1]]);

            // Get relative perpendicular force 
            double perp_force = m_rigid_bodies[collision.body_ids[r]]->getAppliedForce()[1 - collision.axis] - m_rigid_bodies[collision.body_ids[1 - r]]->getAppliedForce()[1 - collision.axis];

            // Make sure static friction force is not larger than the perpendicular force
            if (abs(perp_force) < friction[1 - collision.axis])
            {
                friction[1 - collision.axis] = abs(perp_force);
            }

            // Then apply friction force in opposite direction of relative force
            if (perp_force > 0)
            {
                friction_applied[collision.body_ids[r]] += friction * -1;
            }
            else
            {
                friction_applied[collision.body_ids[r]] += friction;
            }
        }
        else
        {
            friction[1 - collision.axis] = abs(collision.applying_forces[r]) *
                f_physics.getDynamicFrictionCoefficient(m_rigid_bodies[collision.body_ids[0]], m_rigid_bodies[collision.body_ids[1]]);

            const double velocity_diff = m_rigid_bodies[collision.body_ids[r]]->getVelocity()[1 - collision.axis] - m_rigid_bodies[collision.body_ids[1 - r]]->getVelocity()[1 - collision.axis];

            framework::Vector max_friction = { 0, 0 };

            // For balancing out forces in the same direction (- * - = + and + * + = +)
            if (m_rigid_bodies[collision.body_ids[r]]->getAppliedForce()[1 - collision.axis] * velocity_diff >= 0)
            {
                max_friction[1 - collision.axis] = abs(m_rigid_bodies[collision.body_ids[r]]->getAppliedForce()[1 - collision.axis]);

            }

            // For stopping dynamic friction force from changing velocity direction
            if (m_rigid_bodies[collision.body_ids[1 - r]]->isStatic())
            {
                max_friction[1 - collision.axis] += abs(velocity_diff * m_rigid_bodies[collision.body_ids[r]]->getMass() / (f_physics.getTimeStep() - time_passed));

            }
            else
            {
                max_friction[1 - collision.axis] += abs(velocity_diff / 2 * m_rigid_bodies[collision.body_ids[r]]->getMass() / (f_physics.getTimeStep() - time_passed));

            }

            if (friction[1 - collision.axis] > max_friction[1 - collision.axis])
            {
                friction = max_friction;
            }

            // Get relative direction of object
            if (velocity_diff > 0)
            {
                friction_applied[collision.body_ids[r]] += friction * -1;
            }
            else
            {
                friction_applied[collision.body_ids[r]] += friction;
            }
        }
    }
}
