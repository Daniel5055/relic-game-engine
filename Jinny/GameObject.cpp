#include "GameObject.h"

#include <utility>

#include "GameObjectManager.h"

int relic::GameObject::m_next_id_num = 1;
const std::string relic::GameObject::k_object_id_type = "Object";

void relic::GameObject::addComponent(Component* component)
{
    component->setId(m_id, static_cast<int>(m_components.size()));

    m_components.push_back(std::unique_ptr<Component>(component));

    // Informs that the component was incorporated to whomever is listening
    sendImmediateMessage({ ObjectType::component_incorporated, component->getId().getSubId() });
}

void relic::GameObject::update() const
{
    for (const auto& component : m_components)
    {
        component->update();
    }
}

const relic::Identifier& relic::GameObject::getId() const
{
    return m_id;
}

relic::GameObject::GameObject(std::string&& name)
    : MessageSender<relic::ObjectType>(getId()), m_id(m_next_id_num, std::move(name), k_object_id_type)
{
    m_next_id_num++;
}

