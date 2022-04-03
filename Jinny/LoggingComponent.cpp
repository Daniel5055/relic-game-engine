#include "LoggingComponent.h"

#include "Logger.h"

jinny::LoggingComponent::LoggingComponent()
    :m_logger("Object")
{
    m_logger.log("Initialised");
}

jinny::LoggingComponent::~LoggingComponent()
{
    m_logger.log("Destructed");
}

void jinny::LoggingComponent::handleEvent(const ObjectEvent msg)
{
    // Todo: Room for improvement
    switch (msg.type)
    {
    case ObjectEvent::Type::input_triggered:
        switch (msg.input.type)
        {
        case ObjectInputType::left_mouse_down:
            m_logger.log("Left Mouse Button Down Input");
            break;

        case ObjectInputType::left_mouse_up:
            m_logger.log("Left Mouse Button UP Input");
            break;
        case ObjectInputType::key_down:
            m_logger.log(std::string(1, msg.input.key) + " pressed down");
            break;
        case ObjectInputType::key_up:
            m_logger.log(std::string(1, msg.input.key) + " pressed up");
            break;
        }
    case ObjectEvent::Type::component_incorporated:
        m_logger.setLocation(getObjectName());
        break;
    }
}
