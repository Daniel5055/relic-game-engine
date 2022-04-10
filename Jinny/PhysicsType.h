#pragma once

namespace relic
{
    enum class PhysicsSystemType
    {
        set_rigid_body,
        remove_rigid_body,
        register_collision_checking,
        add_material,
        set_material_restitution_coefficient,
        set_material_dynamic_friction,
        set_material_static_friction,

        set_physics_engine
    };

    enum class PhysicsObjectType
    {
        collision_occurred,
    };
}
        
