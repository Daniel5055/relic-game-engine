#pragma once

#include <string>

#include "MessageReceiver.h"
#include "LazyMessageSender.h"
#include "ObjectEvent.h"

namespace relic
{
    // Base class for components
    class Component
        : public MessageReceiver<ObjectEvent>
        , public LazyMessageSender<ObjectEvent>
    {


    public:

        // Prevent ambiguity 
        using LazyMessageSender<ObjectEvent>::addReceiver;

        // Aliasing of receiveMessage method for events to help with clarity and ambiguity with pushing events to systems
        auto receiveEvent(ObjectEvent e)->decltype(receiveMessage(std::forward<ObjectEvent>(e)))
        {
            return receiveMessage(std::forward<ObjectEvent>(e));
        }

        auto receiveImmediateEvent(ObjectEvent e)->decltype(receiveImmediateMessage(std::forward<ObjectEvent>(e)))
        {
            return receiveImmediateMessage(std::forward<ObjectEvent>(e));
        }

        // Virtual destructor because component pointers would likely be deleted
        virtual ~Component() = default;

        // Updating
        void update();

        Message::Type getMessageType();
        void setObjectId(int id);
        void setObjectName(const std::string& name);


    protected:
        int getObjectId() const;
        std::string getObjectName() const;
        

        // Aliasing of sendMessage method for events to help with clarity and ambiguity with sending messages to systems
        auto sendEvent(ObjectEvent e)->decltype(sendMessage(std::forward<ObjectEvent>(e)))
        {
            return sendMessage(std::forward<ObjectEvent>(e));
        }


        // Constant
        static const int k_unset_id;
        static const std::string k_unset_string;
    private:

        // Private virtual methods
        virtual void doUpdates() {}

        void handleMessage(ObjectEvent msg) final;

        // Renaming of handleMessage to handleEvent to improve clarity
        virtual void handleEvent(ObjectEvent e) {}

        // For prepping messages if they were sent before object id set
        void prepareMessage(ObjectEvent& e) final;

        // Defining of message types
        virtual Message::Type defineMessageType();

        // Object identification
        int m_object_id{ k_unset_id };
        std::string m_object_name;
    };
}


