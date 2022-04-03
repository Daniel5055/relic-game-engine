#include "Component.h"

const std::string jinny::Component::k_unset_string = "$";
constexpr int jinny::Component::k_unset_id = -2;

void jinny::Component::update()
{
    handleMessages();

    doUpdates();
}

jinny::Message::Type jinny::Component::getMessageType()
{
    return defineMessageType();
}

void jinny::Component::setObjectId(const int id)
{
    m_object_id = id;
}

void jinny::Component::setObjectName(const std::string& name)
{
    m_object_name = name;
}

int jinny::Component::getObjectId() const
{
    return m_object_id;
}

std::string jinny::Component::getObjectName() const
{
    return m_object_name;
}

void jinny::Component::handleMessage(const ObjectEvent msg)
{
    handleEvent(msg);
}

void jinny::Component::prepareMessage(ObjectEvent& e)
{
    // Nothing needed to prep so far
}

jinny::Message::Type jinny::Component::defineMessageType()
{
    return Message::Type::none;
}
