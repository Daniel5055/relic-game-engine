#pragma once

#include "Component.h"
#include "LazyMessageSender.h"
#include "GraphicsMessage.h"

// Framework Dependencies
#include "Graphic.h"


namespace jinny
{
    /**
     * \brief Base abstract class for components relating to graphics
     */
    class GraphicsComponent : 
        public Component,
        public LazyMessageSender<GraphicsMessage>
    {
    public:
        // Prevent ambiguity
        using LazyMessageSender<GraphicsMessage>::addReceiver;
        using LazyMessageSender<GraphicsMessage>::sendMessage;

        // Accessors
        void setClipPtr(const framework::Shape* clip);
        framework::Graphic& getGraphic();
    protected:
        // Graphic Accessor
        void setGraphic(framework::Graphic* graphic_ptr);
    private:
        // Defining as graphics type 
        Message::Type defineMessageType() final { return Message::Type::graphics; }

        // Defining message prepping
        void prepareMessage(GraphicsMessage& msg) override;

        // Graphic Data
        std::unique_ptr<framework::Graphic> m_graphic_ptr;
    };
}
