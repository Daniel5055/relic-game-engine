#include "LoggingComponent.h"

#include "Logger.h"
#include "ObjectInput.h"

relic::LoggingComponent::LoggingComponent()
    :MessageReceiver<ObjectType>(getObjectId(), true), m_logger(getObjectId())
{
}

relic::LoggingComponent::~LoggingComponent()
{
    m_logger.log("Destructed");
}

void relic::LoggingComponent::doUpdates()
{
    Component::doUpdates();
    handleMessages();
}


void relic::LoggingComponent::handleMessage(const Message<ObjectType>& msg)
{
    // Todo: Room for improvement
    switch (msg.type)
    {
    case ObjectType::input_triggered:
    {
        const auto o_e = std::any_cast<ObjectInput>(msg.value);
        switch (o_e.type)
        {
        case ObjectInputType::left_mouse_down:
            m_logger.log("Left Mouse Button Down Input");
            break;

        case ObjectInputType::left_mouse_up:
            m_logger.log("Left Mouse Button UP Input");
            break;
        case ObjectInputType::key_down:
            m_logger.log(std::string(1, o_e.key) + " pressed down");
            break;
        case ObjectInputType::key_up:
            m_logger.log(std::string(1, o_e.key) + " pressed up");
            break;
        }
        break;
    }
    case ObjectType::component_incorporated:
    {
        if (std::any_cast<Component*>(msg.value) == this)
        {
            m_logger.log("Initialised");
        }
    }
    }
}
