#include "Logger.h"

#include <iostream>

framework::Logger::Logger(const relic::Identifier& id)
    :m_id(id)
{
}

void framework::Logger::log(const std::string& text) const
{
    std::cout << m_id.getName() << ": " << text << std::endl;
}

void framework::Logger::logError(const std::string& text) const
{
    std::cout << m_id.getName() << " Error : " << text << std::endl;
}
