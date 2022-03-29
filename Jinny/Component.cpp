#include "Component.h"

Jinny::Component::Component()
{
    m_object = nullptr;
}

void Jinny::Component::setObject(GameObject* object)
{
    m_object = object;
}

Jinny::GameObject* Jinny::Component::getObject()
{
    return m_object;
}
