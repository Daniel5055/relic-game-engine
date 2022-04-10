#pragma once

#include "InputComponent.h"

#include "Shape.h"

namespace relic
{
    /**
     * \brief Component that subscribes to left mouse button pressing and hovering
     */
    class MouseInputComponent
        : public InputComponent
        , public MessageReceiver<ObjectType>
    {
    public:
        // Constructor
        explicit MouseInputComponent(framework::Shape mouse_area);

    protected:
        // Overriding update method
        void doUpdates() override;
    private:
        // Handling messages
        void handleMessage(Message<InputObjectType> msg) override;
        void handleMessage(Message<ObjectType> msg) override;

        // Members
        bool m_mouse_button_down{ false };
        framework::Shape m_mouse_area;
    };
}