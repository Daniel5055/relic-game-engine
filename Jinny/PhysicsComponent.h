#pragma once

#include "Component.h"

#include "PhysicsMessage.h"

#include "MessageBoard.h"

namespace Jinny
{

    struct PhysicsMessage;

    class PhysicsComponent : public Component
    {
    public:

        // --- pure virtual functions ---

        // Initialization
        virtual void initialize(GameObject& object);

        // Updating
        virtual void update();

        // Closing
        virtual void close();

        // --- functions ---
        void recieveMessage(PhysicsMessage p_msg);

        // To set messageBoard
        static void setMessageBoard(MessageBoard<PhysicsMessage>* message_board);

    protected:
        // --- inherited functions ---

        // Pops Message from queue
        PhysicsMessage popMessage();

        // --- inherited virtual functions ---

        // Event Handling
        virtual void handleEvents();

        // Message Handling
        virtual void handleMessages();

        // Message Pushing
        void pushMessage(PhysicsMessage p_msg);

    private:
        // --- Data ---

        // Message Queue
        std::queue<PhysicsMessage> m_message_queue;

        bool is_static;

        // Access to message board
        static MessageBoard<PhysicsMessage>* m_message_board;

    };

}

