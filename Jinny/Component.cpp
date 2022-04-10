#include "Component.h"

#include "Message.h"

void relic::Component::update()
{
    doUpdates();
}

void relic::Component::setObjectId(const Identifier& id)
{
    m_id = id;
}

const relic::Identifier& relic::Component::getObjectId() const
{
    return m_id;
}
