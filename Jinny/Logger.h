#pragma once

#include <string>

namespace Framework
{
	class Logger
	{
	public:
		Logger(std::string location);

		void log(std::string text);
		void logError(std::string text);

	private:
		std::string m_location;
	};
}


