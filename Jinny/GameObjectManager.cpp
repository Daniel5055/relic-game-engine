#include "GameObjectManager.h"

#include <utility>

#include "GameObject.h"

void relic::GameObjectManager::updateObjects()
{
    for (auto it = m_scene_objects.begin(); it != m_scene_objects.end(); ++it)
    {
        it->get()->update();
    }
    for (auto it = m_global_objects.begin(); it != m_global_objects.end(); ++it)
    {
        it->get()->update();
    }
}

relic::GameObject& relic::GameObjectManager::createObject(std::string name, const bool is_global)
{
    // Either a new global object or new scene object pointer
    // Have to use new as game object constructor is hidden
    if (is_global)
    {
        m_global_objects.push_back(std::unique_ptr<GameObject>(new GameObject(std::move(name))));
        return *m_global_objects.back();
    }
    else
    {
        m_scene_objects.push_back(std::unique_ptr<GameObject>(new GameObject(std::move(name))));
        return *m_scene_objects.back();
    }
}

void relic::GameObjectManager::deleteObject(const Identifier& id)
{
    std::vector<std::unique_ptr<GameObject>>::iterator it;

    for (it = m_global_objects.begin(); it != m_global_objects.end(); ++it)
    {
        if (it->get()->getId() == id)
        {
            m_global_objects.erase(it);
            break;
        }
    }

    if (it != m_global_objects.end())
    {
        for (it = m_scene_objects.begin(); it != m_scene_objects.end(); ++it)
        {
            if (it->get()->getId() == id)
            {
                m_scene_objects.erase(it);
                break;
            }
        }
    }

    if (it != m_scene_objects.end())
    {
        // ERROR
    }
}

void relic::GameObjectManager::clearSceneObjects()
{
    // clear vector
    m_scene_objects.clear();
}

void relic::GameObjectManager::clearGlobalObjects()
{
    m_global_objects.clear();
}
