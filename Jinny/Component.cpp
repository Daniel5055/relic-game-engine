#include "Component.h"

const std::string relic::Component::k_unset_string = "$";
constexpr int relic::Component::k_unset_id = -2;

void relic::Component::update()
{
    handleMessages();

    doUpdates();
}

relic::Message::Type relic::Component::getMessageType()
{
    return defineMessageType();
}

void relic::Component::setObjectId(const int id)
{
    m_object_id = id;
}

void relic::Component::setObjectName(const std::string& name)
{
    m_object_name = name;
}

int relic::Component::getObjectId() const
{
    return m_object_id;
}

std::string relic::Component::getObjectName() const
{
    return m_object_name;
}

void relic::Component::handleMessage(const ObjectEvent msg)
{
    // Deploy messages upon component incorporation
    handleEvent(msg);
}

void relic::Component::prepareMessage(ObjectEvent& e)
{
    // Nothing needed to prep so far
}

relic::Message::Type relic::Component::defineMessageType()
{
    return Message::Type::none;
}
