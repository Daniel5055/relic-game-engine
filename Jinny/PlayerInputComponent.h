#pragma once

#include <map>

#include "InputComponent.h"

namespace jinny
{
    /**
     * \brief Component that subscribes to wasd keys
     */
    class PlayerInputComponent : public InputComponent
    {
    public:
        PlayerInputComponent();
    private:
        void doUpdates() override;
        void handleMessage(InputMessage msg) override;

        std::map<char, bool> m_keys_down;
    };
}