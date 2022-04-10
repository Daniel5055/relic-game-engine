#pragma once

#include "Component.h"

#include "Logger.h"
#include "MessageReceiver.h"
#include "ObjectType.h"

namespace relic
{
    /**
     *\brief Component which logs the actions of the object
     */
    class LoggingComponent final
        : public Component
        , public MessageReceiver<ObjectType>
    {
    public:
        LoggingComponent();
        ~LoggingComponent() override;
    protected:
        void doUpdates() override;

    private:
        void handleMessage(Message<ObjectType> msg) override;

        // --- Data ---
        framework::Logger m_logger;
    };
}