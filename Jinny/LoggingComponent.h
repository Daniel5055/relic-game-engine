#pragma once

#include "Component.h"

#include "Logger.h"

namespace relic
{
    /**
     *\brief Component which logs the actions of the object
     */
    class LoggingComponent final : public Component
    {
    public:
        LoggingComponent();
        ~LoggingComponent() override;
    private:
        void handleEvent(ObjectEvent msg) override;

        // --- Data ---
        framework::Logger m_logger;
    };
}