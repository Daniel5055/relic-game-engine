#pragma once

#include <map>
#include <memory>
#include <string>

#include "Component.h"
#include "GraphicsComponent.h"
#include "InputComponent.h"
#include "CoreComponent.h"
#include "PhysicsComponent.h"
#include "MessageReceiver.h"
#include "ObjectEvent.h"

// Pre define State class
class State;

namespace relic
{
    class MultiMessageReceiver;

    /**
     * \brief Creates and manages game objects
     */
    class GameObjectManager
    {
    public:
        // Game object Class
        class GameObject final
            : public MessageReceiver<ObjectEvent>
        {
            // So that Manager can access constructor and important data
            friend GameObjectManager;

        public:
            // Add Components
            void addComponent(Component* component);

            // Update
            void update();

            // Receiving messages from systems
            template<typename M>
            void pushExternalMessage(M msg);

            // Accessors
            int getId() const;
            std::string getObjectName() const;
        private:
            // Private constructor so that only manager can make objects
            // Passing name by rvalue reference because I know name will always be passed by rvalue
            GameObject(std::string&& name, int id, MultiMessageReceiver& receiver);

            // Overriding event handling to pass events to the components
            void handleMessage(ObjectEvent event) override;

            // --- Data ---

            // Identification
            const std::string m_name;
            const int m_id;

            // All components contained by the game object
            std::vector<std::unique_ptr<Component>> m_components;

            // Reference to receiver of messages sent outwards by messages 
            MultiMessageReceiver& m_receiver;
        };

    public:
        explicit GameObjectManager(MultiMessageReceiver& receiver);
        // Factory creation method of game object
        GameObject& createObject(std::string name, bool is_global = false);

        // Update method
        void updateObjects();

        // Accessor
        GameObject& getObject(int id);

        // Deletion
        void deleteObject(int id);

        // Clear entire object list, size reset
        void clearSceneObjects();
        void clearGlobalObjects();

    private:
        // Store object pointers
        std::map<int, std::unique_ptr<GameObject>> m_scene_objects{};
        std::map<int, std::unique_ptr<GameObject>> m_global_objects{};

        // Next index 
        int m_next_index{ 1 };

        // Reference to receiver of external messages sent by objects
        MultiMessageReceiver& m_receiver;
    };

    template <typename M>
    void GameObjectManager::GameObject::pushExternalMessage(M msg)
    {
        // Cast to message to get data
        static_assert(std::is_base_of_v<InputMessage, M>);
        // TODO: work around only works inputmessages
        const auto base_msg = static_cast<InputMessage>(msg);

        for (const auto& component : m_components)
        {
            if (component->getMessageType() == base_msg.getType())
            {
                switch(base_msg.getType())
                {
                case Message::Type::graphics:
                    break;
                case Message::Type::input: 
                    // So fat only input component accepts messages but I might change this
                    static_cast<InputComponent*>(component.get())->receiveMessage(msg);
                    break;
                case Message::Type::physics: break;
                case Message::Type::core: break;
                default: ;
                }
                
            }
        }
    }
}
