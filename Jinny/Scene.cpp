#include "Scene.h"

#include "MouseInputComponent.h"
#include "ImageGraphicsComponent.h"

#include "CameraCoreComponent.h"

#include "AssetLoaderGraphicsComponent.h"


jinny::GameObjectManager* jinny::Scene::m_object_manager;
unsigned int jinny::Scene::m_window_width;
unsigned int jinny::Scene::m_window_height;

void jinny::Scene::initialise()
{
    doInitialisation();
}

void jinny::Scene::setObjectManager(GameObjectManager* object_manager)
{
    m_object_manager = object_manager;
}

void jinny::Scene::setWindowSize(const unsigned int width, const unsigned int height)
{
    m_window_width = width;
    m_window_height = height;
}

void jinny::Scene::setScope(const bool is_global)
{
    m_is_global_scope = is_global;
}

unsigned int jinny::Scene::getWindowWidth()
{
    return m_window_width;
}

unsigned int jinny::Scene::getWindowHeight()
{
    return m_window_height;
}

void jinny::Scene::loadAssets(const std::map<std::string, std::pair<std::string, unsigned int>>& assets) const
{
    auto& asset_loader = m_object_manager->createObject("Asset loader");
    asset_loader.addComponent(new AssetLoaderGraphicsComponent(assets));

    // Now that messages are sent, delete object
    m_object_manager->deleteObject(asset_loader.getId());
}

void jinny::Scene::createCamera(const framework::Shape camera) const
{
    auto& o = m_object_manager->createObject("Camera Setter");
    o.addComponent(new CameraCoreComponent(new framework::Shape(camera)));
    m_object_manager->deleteObject(o.getId());
}
