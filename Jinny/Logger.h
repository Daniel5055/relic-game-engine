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

        static void log(const relic::Identifier& id, const std::string& text);
        static void logInfo(const relic::Identifier& id, const std::string& text);
        static void logWarning(const relic::Identifier& id, const std::string& text);
        static void logError(const relic::Identifier& id, const std::string& text);
    private:
        const relic::Identifier& m_id;
    };
}


