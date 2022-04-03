#pragma once

#include <string>

namespace framework
{
    /**
     * Class used to log information.
     */
    class Logger
    {
    public:
        // Constructor
        explicit Logger(std::string location);

        // Logging functions
        void log(std::string text) const;
        void logError(std::string text) const;

        void setLocation(std::string location);

    private:
        std::string m_location;
    };
}


