#pragma once

#include "Component.h"
#include "MessageReceiver.h"
#include "MessageSender.h"
#include "ButtonType.h"
#include "GraphicsType.h"

namespace relic
{
    /**
     * \brief Handles button logic like on press, and notifies any animation component of state changes
     */
    class ButtonLogicComponent
        : public Component
        , public MessageReceiver<ButtonType>
        , public MessageSender<GraphicsObjectType>
    {
    public:
        ButtonLogicComponent();
    protected:
        void doUpdates() override;

        enum class ButtonState
        {
            button_neutral = 0,
            button_focused = 1,
            button_down = 2,
        };

    private:

        // On button press
        virtual void onPress() {}

        void handleMessage(const Message<ButtonType>& msg) override;

    };
}
