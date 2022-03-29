#pragma once

#include "Component.h"

namespace Framework
{
    class Logger;
}

namespace Jinny
{


    class LoggingComponent : public Component
    {
    public:

        // Initialization
        void initialize(GameObject& object);

        void update();

        void close();

        // Destructor
        ~LoggingComponent();

    private:
        // Event Handling
        void handleEvents();

        // --- Data ---
        Framework::Logger* m_logger;
    };
}