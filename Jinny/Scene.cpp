#include "Scene.h"

#include "MouseInputComponent.h"
#include "ImageGraphicsComponent.h"

#include "CameraCoreComponent.h"

#include "AssetLoaderGraphicsComponent.h"

// apperently necessary?
#include "AssetLoaderGraphicsComponent.cpp"


Jinny::GameObjectManager* Jinny::Scene::m_object_manager;
unsigned int Jinny::Scene::m_window_width;
unsigned int Jinny::Scene::m_window_height;

Jinny::Scene::Scene()
{
    m_is_global_scope = false;
}

void Jinny::Scene::setObjectManager(GameObjectManager* object_manager)
{
    m_object_manager = object_manager;
}

void Jinny::Scene::setWindowSize(unsigned int width, unsigned int height)
{
    m_window_width = width;
    m_window_height = height;
}

void Jinny::Scene::setScope(bool is_global)
{
    m_is_global_scope = is_global;
}

void Jinny::Scene::addWorldObject(GameObject* object)
{
    if (m_is_global_scope)
    {
        m_object_manager->addGlobalWorldObject(object);
    }
    else
    {
        m_object_manager->addSceneWorldObject(object);
    }
}

void Jinny::Scene::addHUDObject(GameObject* object)
{
    if (m_is_global_scope)
    {
        m_object_manager->addGlobalHUDObject(object);
    }
    else
    {
        m_object_manager->addSceneHUDObject(object);
    }
}

unsigned int Jinny::Scene::getWindowWidth() const
{
    return m_window_width;
    return 0;
}

unsigned int Jinny::Scene::getWindowHeight() const
{
    m_window_height;
    return 0;
}

void Jinny::Scene::loadAssets(std::map<std::string, std::pair<std::string, unsigned int>> assets)
{
    addHUDObject(new GameObject("Asset Loader", {}, new AssetLoaderGraphicsComponent(assets)));

    // Now that messages are sent, delete object
    m_object_manager->deleteObject(m_object_manager->nextID() - 1);
}

Jinny::GameObject* Jinny::Scene::createButtonSkeleton(std::string name, Framework::Shape shape, std::string texture_name)
{
    GameObject* button = new GameObject(name, shape, new ImageGraphicsComponent(texture_name), new MouseInputComponent());
    return nullptr;
}

Jinny::GameObject* Jinny::Scene::createCamera(Framework::Shape camera_boundaries)
{
    GameObject* camera = new GameObject("Camera", camera_boundaries, nullptr, nullptr, nullptr, new  CameraCoreComponent());
    addWorldObject(camera);

    return camera;
}
