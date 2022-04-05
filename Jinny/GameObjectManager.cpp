#include "GameObjectManager.h"

#include <utility>

#include "MultiMessageReceiver.h"

relic::GameObjectManager::GameObject::GameObject(std::string&& name, const int id, MultiMessageReceiver& receiver)
    : m_name(std::move(name)), m_id(id), m_receiver(receiver)
{
}

void relic::GameObjectManager::GameObject::addComponent(Component* component)
{
    // Add game object as receiver of event messages (of which it will eventually distribute)
    component->addReceiver(this);

    // Set identification
    component->setObjectId(m_id);
    component->setObjectName(m_name);

    // Notify component that component has been connected to object
    const ObjectEvent e{ ObjectEvent::Type::component_incorporated };
    component->receiveImmediateEvent(e);
    component->deployMessages();

    // Determine type of component, then cast and set receiver
    switch (component->getMessageType())
    {
    case Message::Type::graphics:
    {

        const auto graphics_component = dynamic_cast<GraphicsComponent*>(component);
        graphics_component->addReceiver(&m_receiver);
        graphics_component->deployMessages();
        break;

    }
    case Message::Type::input:
    {
        const auto input_component = dynamic_cast<InputComponent*>(component);
        input_component->addReceiver(&m_receiver);
        input_component->deployMessages();
        break;

    }
    case Message::Type::physics:
    {
        const auto physics_component = dynamic_cast<PhysicsComponent*>(component);
        physics_component->addReceiver(&m_receiver);
        physics_component->deployMessages();
        break;

    }
    case Message::Type::core:
    {
        const auto core_component = dynamic_cast<CoreComponent*>(component);
        core_component->addReceiver(&m_receiver);
        core_component->deployMessages();
        break;
    }
    default:;
    }
    m_components.push_back(std::unique_ptr<Component>(component));
}

void relic::GameObjectManager::GameObject::update()
{
    // Distribute events to components
    handleMessages();

    // Update components
    for (const auto& component : m_components)
    {
        component->update();
    }
}

int relic::GameObjectManager::GameObject::getId() const
{
    return m_id;
}

std::string relic::GameObjectManager::GameObject::getObjectName() const
{
    return m_name;
}

void relic::GameObjectManager::GameObject::handleMessage(const ObjectEvent event)
{
    // Push event to all components
    for (const auto& component : m_components)
    {
        component->receiveMessage(event);
    }
}

relic::GameObjectManager::GameObjectManager(MultiMessageReceiver& receiver)
    :m_receiver(receiver)
{
}

relic::GameObjectManager::GameObject& relic::GameObjectManager::createObject(std::string name, const bool is_global)
{
    // If global or not
    // Returns and increment index simultaneously
    if (is_global)
    {
        m_global_objects.insert({ m_next_index, std::unique_ptr<GameObject>(new GameObject(std::move(name), m_next_index, m_receiver)) });
        return *m_global_objects[m_next_index++].get();
    }

    m_scene_objects.insert({ m_next_index, std::unique_ptr<GameObject>(new GameObject(std::move(name), m_next_index, m_receiver)) });
    return *m_scene_objects[m_next_index++].get();
}

void relic::GameObjectManager::updateObjects()
{
    for (auto it = m_scene_objects.begin(); it != m_scene_objects.end(); ++it)
    {
        if (it->second != nullptr)
        {
            it->second->update();
        }
    }
    for (auto it = m_global_objects.begin(); it != m_global_objects.end(); ++it)
    {
        if (it->second != nullptr)
        {
            it->second->update();
        }
    }
}

relic::GameObjectManager::GameObject& relic::GameObjectManager::getObject(const int id)
{
    // TODO: Error handling

    // Find in scene objects, else find in global
    const auto it = m_scene_objects.find(id);
    if (it != m_scene_objects.end())
    {
        return *it->second;
    }

    return *m_global_objects[id];
}


void relic::GameObjectManager::deleteObject(const int id)
{
    auto it = m_scene_objects.find(id);
    if (it != m_scene_objects.end())
    {
        // Delete
        m_scene_objects.erase(it);
    }
    else
    {
        it = m_global_objects.find(id);
        if (it != m_global_objects.end())
        {

            // Delete
            m_global_objects.erase(it);
        }
    }

    // Else nothing cleared
    // TODO: Maybe log this as warning?
}

void relic::GameObjectManager::clearSceneObjects()
{
    // clear vector
    m_scene_objects.clear();
}

void relic::GameObjectManager::clearGlobalObjects()
{
    // clear vector
    m_global_objects.clear();
}
