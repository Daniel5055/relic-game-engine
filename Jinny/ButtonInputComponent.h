#pragma once

#include "InputComponent.h"
#include "MessageReceiver.h"
#include "MessageSender.h"
#include "ObjectType.h"
#include "ButtonType.h"

#include "Shape.h"

namespace relic
{
    /**
     * \brief Component that subscribes to left mouse button pressing and hovering
     */
    class ButtonInputComponent
        : public InputComponent
        , public MessageReceiver<ObjectType>
        , public MessageSender<ButtonType>
    {
    public:
        // Constructor
        explicit ButtonInputComponent(framework::Shape mouse_area);

    protected:
        // Overriding update method
        void doUpdates() override;
    private:
        // Handling messages
        void handleMessage(const Message<ObjectType>& msg) override;
        void handleMessage(const Message<InputObjectType>& msg) override;

        // Members
        bool m_mouse_button_down{ false };
        framework::Shape m_mouse_area;
    };
}