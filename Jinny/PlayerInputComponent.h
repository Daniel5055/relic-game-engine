#pragma once

#include <map>

#include "InputComponent.h"

namespace relic
{
    /**
     * \brief Component that subscribes to wasd keys
     */
    class PlayerInputComponent
        : public InputComponent
    {
    public:
        PlayerInputComponent();
    private:
        void handleMessage(const Message<InputObjectType>& msg) override;

        std::map<char, bool> m_keys_down;
    };
}