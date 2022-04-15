#include "LoggingSystem.h"

#include "Logger.h"

relic::LoggingSystem::LoggingSystem()
    :GameSystem("Logging System"), MessageReceiver(getId())
{
}

void relic::LoggingSystem::doUpdates()
{
    handleMessages();
}

void relic::LoggingSystem::handleMessage(const Message<LoggingType>& msg)
{
    const int type_code = static_cast<int>(msg.type);
    const std::string text = std::any_cast<std::string>(msg.value);

    if (type_code >= k_error_messages_code)
    {
        framework::Logger::logError(msg.from, toString(msg.type) + " - " + text);
    }
    else if (type_code >= k_warning_messages_code)
    {
        framework::Logger::logWarning(msg.from, text);
    }
    else if (type_code >= k_info_messages_code)
    {
        framework::Logger::logInfo(msg.from, text);
    }
    else
    {
        framework::Logger::logError(getId(), "Invalid message type code received");
    }
}
