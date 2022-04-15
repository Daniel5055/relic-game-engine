#include "Scene.h"

#include <utility>

#include "ImageGraphicsComponent.h"

#include "CameraCoreComponent.h"

#include "AssetLoaderGraphicsComponent.h"
#include "GameObjectManager.h"


unsigned int relic::Scene::m_window_width;
unsigned int relic::Scene::m_window_height;

relic::GameObjectManager* relic::Scene::m_object_manager;

void relic::Scene::initialise()
{
    doInitialisation();
}

void relic::Scene::setWindowSize(const unsigned int width, const unsigned int height)
{
    m_window_width = width;
    m_window_height = height;
}

void relic::Scene::setObjectManager(GameObjectManager* object_manager)
{
    m_object_manager = object_manager;
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
    GameObject& object = createObject("Asset loader");
    object.addComponent(new AssetLoaderGraphicsComponent(assets));
}

void relic::Scene::createCamera(const framework::Shape camera) const
{
    GameObject& o = createObject("Camera");
    o.addComponent(new CameraCoreComponent(new framework::Shape(camera)));
}

relic::GameObject& relic::Scene::createObject(std::string name, const bool is_global) const
{
    return m_object_manager->createObject(std::move(name), is_global);
}
