#include "GameObjectManager.h"

#include <utility>

#include "MultiMessageReceiver.h"

jinny::GameObjectManager::GameObject::GameObject(std::string&& name, const int id, MultiMessageReceiver& receiver)
    : m_name(std::move(name)), m_id(id), m_receiver(receiver)
{
}

void jinny::GameObjectManager::GameObject::addComponent(Component* component)
{
    // Add game object as receiver of event messages (of which it will eventually distribute)
    component->addReceiver(this);

    // Set identification
    component->setObjectId(m_id);
    component->setObjectName(m_name);

    // Notify component that component has been connected to object
    const ObjectEvent e{ ObjectEvent::Type::component_incorporated };
    component->pushEvent(e);

    // Determine type of component, then cast and set receiver
    switch (component->getMessageType())
    { 
    case Message::Type::graphics:
        dynamic_cast<GraphicsComponent*>(component)->addReceiver(&m_receiver);
        break;
    case Message::Type::input:
        dynamic_cast<InputComponent*>(component)->addReceiver(&m_receiver);
        break;
    case Message::Type::physics:
        dynamic_cast<PhysicsComponent*>(component)->addReceiver(&m_receiver);
        break;
    case Message::Type::core:
        dynamic_cast<CoreComponent*>(component)->addReceiver(&m_receiver);
        break;
    default: ;
    }
    m_components.push_back(std::unique_ptr<Component>(component));
}

void jinny::GameObjectManager::GameObject::update()
{
    // Distribute events to components
    handleMessages();

    // Update components
    for (const auto& component : m_components)
    {
        component->update();
    }
}

int jinny::GameObjectManager::GameObject::getId() const
{
    return m_id;
}

std::string jinny::GameObjectManager::GameObject::getObjectName() const
{
    return m_name;
}

void jinny::GameObjectManager::GameObject::handleMessage(const ObjectEvent event)
{
    // Push event to all components
    for (const auto& component : m_components)
    {
        component->pushMessage(event);
    }
}

jinny::GameObjectManager::GameObjectManager(MultiMessageReceiver& receiver)
    :m_receiver(receiver)
{
}

jinny::GameObjectManager::GameObject& jinny::GameObjectManager::createObject(std::string name, const bool is_global)
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

void jinny::GameObjectManager::updateObjects()
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

jinny::GameObjectManager::GameObject& jinny::GameObjectManager::getObject(const int id)
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


void jinny::GameObjectManager::deleteObject(const int id)
{
    auto it = m_scene_objects.find(id);
    if (it != m_scene_objects.end())
    {
        // Delete
        m_scene_objects.erase(it);
    }
    else
    {
        it  = m_global_objects.find(id);
        if (it != m_global_objects.end())
        {

            // Delete
            m_global_objects.erase(it);
        }
    }

    // Else nothing cleared
    // TODO: Maybe log this as warning?
}

void jinny::GameObjectManager::clearSceneObjects()
{
    // clear vector
    m_scene_objects.clear();
}

void jinny::GameObjectManager::clearGlobalObjects()
{
    // clear vector
    m_global_objects.clear();
}
