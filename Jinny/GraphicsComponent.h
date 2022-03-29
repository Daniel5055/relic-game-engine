#pragma once

#include "Component.h"
#include "GraphicsMessage.h"
#include "MessageBoard.h"

// Framework Dependencies
#include "Graphic.h"


namespace Jinny
{

    class GraphicsComponent : public Component
    {
    public:
        // Constructor
        GraphicsComponent();

        // --- pure virtual functions ---
        // Initialization
        virtual void initialize(GameObject& object);

        // Updating
        virtual void update();

        // Closing
        virtual void close();

        // Destructor
        ~GraphicsComponent();

        // --- functions ---

        // Functions to be used by object
        void recieveMessage(GraphicsMessage g_msg);

        // To set messageBoard
        static void setMessageBoard(MessageBoard<GraphicsMessage>* message_board);

        // For Animation
        void setClipPtr(Framework::Shape* clip);
        Framework::Graphic* getGraphic();

    protected:
        // --- inherited functions ---

        // Graphic Accessor
        void setGraphic(Framework::Graphic* graphic_ptr);

        // --- inherited virtual functions ---

        // Event Handling
        virtual void handleEvents();

        // Message Handling
        virtual void handleMessages();

        // Message Pushing
        void pushMessage(GraphicsMessage g_msg);

        // Message Popping
        GraphicsMessage popMessage();


    private:

        // --- Data ---

        // Message Queue
        std::queue<GraphicsMessage> m_message_queue;

        // Graphicis Data
        Framework::Graphic* m_graphic_ptr;

        // Access to message board
        static MessageBoard<GraphicsMessage>* m_message_board;
    };
}
