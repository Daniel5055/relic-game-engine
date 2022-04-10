#pragma once


#include "Component.h"
#include "MessageReceiver.h"
#include "MessageSender.h"
#include "InputType.h"
#include "ObjectInput.h"
#include "ObjectType.h"
#include "Shape.h"

namespace relic
{
    /**
     * \brief Base abstract class for components relating to input
     */
    class InputComponent
        : public Component
        , public MessageReceiver<InputObjectType>
        , public MessageSender<InputSystemType>
        , public MessageSender<ObjectType>
    {
    protected:
        InputComponent();

        // Useful methods that can be used by derived classes
        void subscribeInput(ObjectInputType type, char key = ' ');

        void subscribeInput(ObjectInputType type, framework::Shape* mouse_area);

        // Virtual methods
        void doUpdates() override;

    };
}


