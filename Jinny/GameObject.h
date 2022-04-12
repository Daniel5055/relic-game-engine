#pragma once
#include <memory>
#include <vector>

#include "MessageSender.h"
#include "Component.h"
#include "Identifier.h"
#include "GameObject.h"
#include "ObjectType.h"

namespace relic
{
    class GameObjectManager;

    /**
     * \brief The object class, basically a wrapper class for a collection of components
     */
    class GameObject final
        : MessageSender<ObjectType>
    {
        // So that the manager can access constructor
        friend GameObjectManager;

    public:
        // To stop the copying and creation of game objects in any other manner besides the GameObjectManager
        GameObject(const GameObject& object) = delete;
        GameObject(const GameObject&& object) = delete;
        GameObject& operator=(const GameObject& object) = delete;
        GameObject& operator=(const GameObject&& object) = delete;

        // Add Components
        void addComponent(Component* component);

        // Update
        void update() const;

        // Accessor
        const Identifier& getId() const;

    private:
        // Private constructor so that only manager can create objects, using rvalue reference for string as we know manager will perform std::move on passing string
        explicit GameObject(std::string&& name);

        // Identification
        const Identifier m_id;

        // All components contained by the game object
        std::vector<std::unique_ptr<Component>> m_components{};

        // Static members
        static int m_next_id_num;
        const static std::string k_object_id_type;
    };
}
