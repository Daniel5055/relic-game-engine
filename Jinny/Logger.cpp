#include "Logger.h"

#include <iostream>

framework::Logger::Logger(const std::string location)
    :m_location(location)
{
}

void framework::Logger::log(const std::string text) const
{
    std::cout << m_location << ": " << text << std::endl;
}

void framework::Logger::logError(const std::string text) const
{
    std::cout << m_location << " Error : " << text << std::endl;
}

void framework::Logger::setLocation(const std::string location)
{
    m_location = location;
}
