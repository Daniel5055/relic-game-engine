#pragma once

#include <string>

namespace Framework
{
    /**
     * Class used to log information.
     */
    class Logger
    {
    public:
        // Constructor
        explicit Logger(std::string t_location);

        // Logging functions
        void log(std::string t_text) const;
        void logError(std::string t_text) const;

    private:
        std::string m_location;
    };
}


