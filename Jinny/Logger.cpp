#include "Logger.h"

#include <iostream>

Framework::Logger::Logger(std::string t_location)
    :m_location(t_location)
{
}

void Framework::Logger::log(std::string text) const
{
    std::cout << m_location << ": " << text << std::endl;
}

void Framework::Logger::logError(std::string text) const
{
    std::cout << m_location << " Error : " << text << std::endl;
}
