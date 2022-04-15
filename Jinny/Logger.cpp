#include "Logger.h"

#include <iostream>

framework::Logger::Logger(const relic::Identifier& id)
    :m_id(id)
{
}

void framework::Logger::log(const std::string& text) const
{
    log(m_id, text);
}

void framework::Logger::logError(const std::string& text) const
{
    logError(m_id, text);
}

void framework::Logger::log(const relic::Identifier& id, const std::string& text)
{
    std::cout << id.getName() << ": " << text << std::endl;
}

void framework::Logger::logInfo(const relic::Identifier& id, const std::string& text)
{
    std::cout << id.getName() << " - INFO: " << text << std::endl;
}

void framework::Logger::logWarning(const relic::Identifier& id, const std::string& text)
{
    std::cout << id.getName() << " - WARNING: " << text << std::endl;
}

void framework::Logger::logError(const relic::Identifier& id, const std::string& text)
{
    std::cout << id.getName() << " - ERROR: " << text << std::endl;
}
