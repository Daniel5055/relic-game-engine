#include "Scene.h"

#include "MouseInputComponent.h"
#include "ImageGraphicsComponent.h"

#include "CameraCoreComponent.h"

#include "AssetLoaderGraphicsComponent.h"


relic::GameObjectManager* relic::Scene::m_object_manager;
unsigned int relic::Scene::m_window_width;
unsigned int relic::Scene::m_window_height;

void relic::Scene::initialise()
{
    doInitialisation();
}

void relic::Scene::setObjectManager(GameObjectManager* object_manager)
{
    m_object_manager = object_manager;
}

void relic::Scene::setWindowSize(const unsigned int width, const unsigned int height)
{
    m_window_width = width;
    m_window_height = height;
}

void relic::Scene::setScope(const bool is_global)
{
    m_is_global_scope = is_global;
}

unsigned int relic::Scene::getWindowWidth()
{
    return m_window_width;
}

unsigned int relic::Scene::getWindowHeight()
{
    return m_window_height;
}

void relic::Scene::loadAssets(const std::map<std::string, std::pair<std::string, unsigned int>>& assets) const
{
    auto& asset_loader = m_object_manager->createObject("Asset loader");
    asset_loader.addComponent(new AssetLoaderGraphicsComponent(assets));

    // Now that messages are sent, delete object
    m_object_manager->deleteObject(asset_loader.getId());
}

void relic::Scene::createCamera(const framework::Shape camera) const
{
    auto& o = m_object_manager->createObject("Camera Setter");
    o.addComponent(new CameraCoreComponent(new framework::Shape(camera)));
    m_object_manager->deleteObject(o.getId());
}

relic::GameObjectManager::GameObject& relic::Scene::createObject(const std::string& name, const bool is_global)
{
    return m_object_manager->createObject(name, is_global);
}
