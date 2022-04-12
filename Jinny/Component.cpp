#include "Component.h"

#include "Message.h"

void relic::Component::update()
{
    doUpdates();
}

void relic::Component::setId(const Identifier& id, const int component_count)
{
    m_id = id;

    // Setting the sub id
    m_id.setSubId(component_count + 1);
}

const relic::Identifier& relic::Component::getId() const
{
    return m_id;
}
