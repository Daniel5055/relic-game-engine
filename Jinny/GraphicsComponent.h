#pragma once

#include "Component.h"

#include "MessageReceiver.h"
#include "MessageSender.h"
#include "GraphicsType.h"
#include "ObjectType.h"

// Framework Dependencies
#include <memory>

#include "Graphic.h"


namespace relic
{
    /**
     * \brief Base abstract class for components relating to graphics
     */
    class GraphicsComponent 
        : public Component
        , public MessageSender<GraphicsSystemType>
        , public MessageReceiver<ObjectType>
    {
    public:
        // Constructor
        GraphicsComponent();

        // Destructor
        ~GraphicsComponent() override;

        // Accessors
        void setClipPtr(const framework::Shape* clip);
        framework::Graphic& getGraphic() const;
    protected:
        // Graphic Accessor
        void setGraphic(framework::Graphic* graphic_ptr);

        void doUpdates() override;
    private:
        // Graphic Data
        std::unique_ptr<framework::Graphic> m_graphic_ptr;

        void handleMessage(const Message<ObjectType>& msg) override;
    };
}
