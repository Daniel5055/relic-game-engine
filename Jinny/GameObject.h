#pragma once
#include <memory>
#include <vector>

#include "Component.h"
#include "Identifier.h"
#include "GameObject.h"

namespace relic
{
    class GameObjectManager;

    class GameObject final
    {
        // So that Manager can access constructor and important data
        friend GameObjectManager;

    public:

        // Add Components
        void addComponent(Component* component);

        // Update
        void update() const;

        // Accessor
        const Identifier& getId() const;

    private:
        // Private constructor so that only manager can create objects, using rvalue reference for string as we know manager will perform std::move on passing string
        explicit GameObject(std::string&& name);

        GameObject(const GameObject& object) = delete;
        GameObject(const GameObject&& object) = delete;
        GameObject& operator=(const GameObject& object) = delete;
        GameObject& operator=(const GameObject&& object) = delete;
        

        // Identification
        const Identifier m_id;

        // All components contained by the game object
        std::vector<std::unique_ptr<Component>> m_components{};

        // Static members
        static int m_next_id_num;
        const static std::string k_object_id_type;
    };
}
