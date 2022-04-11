#pragma once

#include <string>
#include "Identifier.h"

namespace framework
{
    /**
     * Class used to log information.
     */
    class Logger
    {
    public:
        // Constructor
        explicit Logger(const relic::Identifier& id);

        // Logging functions
        void log(const std::string& text) const;
        void logError(const std::string& text) const;
    private:
        const relic::Identifier& m_id;
    };
}


