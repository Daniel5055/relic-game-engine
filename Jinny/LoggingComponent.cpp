#include "LoggingComponent.h"

#include "Logger.h"


#include <string>


void Jinny::LoggingComponent::initialize(GameObject& object)
{
    // Set Object
    setObject(&object);

    m_logger = new Framework::Logger(object.getObjectName());
    m_logger->log("Initialized");
}

void Jinny::LoggingComponent::update()
{
    handleEvents();
}

void Jinny::LoggingComponent::close()
{
}

Jinny::LoggingComponent::~LoggingComponent()
{
    delete m_logger;
    m_logger = nullptr;
}

void Jinny::LoggingComponent::handleEvents()
{
    for (auto it = getObject()->getQueueIterator(); it != getObject()->getQueueEnd(); it++)
    {
        switch (it->type)
        {
        case EventType::INPUT_TRIGGERED:
            switch (it->input.type)
            {
            case ObjectInputType::LEFT_MOUSE_DOWN:
                m_logger->log("Left Mouse Button Down Input");
                break;

            case ObjectInputType::LEFT_MOUSE_UP:
                m_logger->log("Left Mouse Button UP Input");
                break;
            case ObjectInputType::KEY_DOWN:
                m_logger->log(std::string(1, it->input.key) + " pressed down");
                break;
            case ObjectInputType::KEY_UP:
                m_logger->log(std::string(1, it->input.key) + " pressed up");
                break;
            }

        }

    }
}
