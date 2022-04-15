#pragma once

#include "GameSystem.h"
#include "MessageReceiver.h"
#include "LoggingType.h"

namespace relic
{
    /**
     * \brief System utilised for handling logging messages
     */
    class LoggingSystem final
        : public GameSystem
        , public MessageReceiver<LoggingType>
    {
    public:
        LoggingSystem();

    private:
        void doUpdates() override;
        void handleMessage(const Message<LoggingType>& msg) override;
    };
}
