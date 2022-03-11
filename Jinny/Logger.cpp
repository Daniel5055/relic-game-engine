#include "Logger.h"

#include <iostream>

Framework::Logger::Logger(std::string location)
{
	m_location = location;
}

void Framework::Logger::log(std::string text)
{
	std::cout << m_location << ": " << text << std::endl;

}

void Framework::Logger::logError(std::string text)
{
	std::cout << m_location << " Error : " << text << std::endl;
}
