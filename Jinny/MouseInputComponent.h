#pragma once

#include "InputComponent.h"

#include "Shape.h"

namespace relic
{
    
    /**
     * \brief Component that subscribes to left mouse button pressing and hovering
     */
    class MouseInputComponent : public InputComponent
    {
    public:
        explicit MouseInputComponent(framework::Shape mouse_area);

    private:
        void handleMessage(InputMessage msg) override;
        void handleEvent(ObjectEvent e) override;
        void doUpdates() override;

        bool m_mouse_button_down{false};

        framework::Shape m_mouse_area;
    };


}