#pragma once

#include <map>

#include "InputComponent.h"

namespace Jinny
{
    class PlayerInputComponent : public InputComponent
    {
    public:
        // Initialize
        void initialize(GameObject& object);

        // Updating
        void update();


    private:
        void handleMessages();

        std::map<char, bool> m_keys_down;
    };

}