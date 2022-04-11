#include "GameObject.h"

#include <utility>

#include "GameObjectManager.h"

int relic::GameObject::m_next_id_num = 1;
const std::string relic::GameObject::k_object_id_type = "Object";

void relic::GameObject::addComponent(Component* component)
{
    component->setObjectId(m_id);
    m_components.push_back(std::unique_ptr<Component>(component));

    // Informs that component was incorporated to whomever is listening
    // Passes pointer to component to say which component was incorporated
    // Honestly not a fan of passing pointers to whole components via messages
    // Might find other way to identify components (Maybe component identifier)
    sendImmediateMessage({ ObjectType::component_incorporated, std::make_any<Component*>(component) });
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

