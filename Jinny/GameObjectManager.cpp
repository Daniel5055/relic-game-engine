#include "GameObjectManager.h"

Jinny::GameObjectManager::GameObjectManager()
    :m_global_object_ptrs(), m_scene_object_ptrs(), m_next_index(0)
{
}

void Jinny::GameObjectManager::updateObjects()
{
    for (auto it = m_scene_object_ptrs.begin(); it != m_scene_object_ptrs.end(); it++)
    {
        if (it->second != nullptr)
        {
            it->second->update();
        }
    }
    for (auto it = m_global_object_ptrs.begin(); it != m_global_object_ptrs.end(); it++)
    {
        if (it->second != nullptr)
        {
            it->second->update();
        }
    }
}

void Jinny::GameObjectManager::addSceneWorldObject(GameObject* obj)
{
    obj->setObjectID(m_next_index);


    obj->initialize();

    m_scene_object_ptrs[m_next_index] = std::unique_ptr<GameObject>(obj);

    m_next_index++;
}

void Jinny::GameObjectManager::addGlobalWorldObject(GameObject* obj)
{
    obj->setObjectID(m_next_index);

    obj->initialize();

    m_global_object_ptrs[m_next_index] = std::unique_ptr<GameObject>(obj);

    m_next_index++;
}

void Jinny::GameObjectManager::addSceneHUDObject(GameObject* obj)
{
    // Toggle as HUD object, might make as friend to object
    obj->toggleHUD();

    addSceneWorldObject(obj);
}

void Jinny::GameObjectManager::addGlobalHUDObject(GameObject* obj)
{
    // Toggle as HUD object, might make as friend to object
    obj->toggleHUD();

    addGlobalWorldObject(obj);
}

int Jinny::GameObjectManager::nextID() const
{
    return m_next_index;
}

Jinny::GameObject& Jinny::GameObjectManager::getObject(int ID)
{
    // This is a little inefficient, perhaps faster way developed later?
    auto it = m_scene_object_ptrs.find(ID);
    if (it != m_scene_object_ptrs.end())
    {
        return *it->second;
    }
    else
    {
        return *m_global_object_ptrs[ID];
    }

    // Also no error handling :/
}


void Jinny::GameObjectManager::deleteObject(int ID)
{
    auto it = m_scene_object_ptrs.find(ID);
    if (it != m_scene_object_ptrs.end())
    {
        // Close Object data
        it->second->close();

        // Delete
        it->second.release();
        m_scene_object_ptrs.erase(it);
    }
    else
    {
        auto it = m_global_object_ptrs.find(ID);
        if (it != m_global_object_ptrs.end())
        {
            // Close Object data
            it->second->close();

            // Delete
            m_global_object_ptrs.erase(it);
        }
    }

    // Else nothing cleared
}

void Jinny::GameObjectManager::clearSceneObjects()
{
    // Iterate through each object to close and delete objects;
    for (auto it = m_scene_object_ptrs.begin(); it != m_scene_object_ptrs.end(); it++)
    {
        it->second->close();
    }

    // clear vector
    m_scene_object_ptrs.clear();
}

void Jinny::GameObjectManager::clearGlobalObjects()
{
    // Iterate through each object to close and delete objects;
    for (auto it = m_global_object_ptrs.begin(); it != m_global_object_ptrs.end(); it++)
    {
        it->second->close();

    }

    // clear vector
    m_global_object_ptrs.clear();
}
