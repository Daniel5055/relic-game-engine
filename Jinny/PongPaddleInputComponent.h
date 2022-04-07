#pragma once

#include <map>

#include "InputComponent.h"

namespace relic
{
    namespace pong
    {
        class PongPaddleInputComponent final : public InputComponent
        {
        public:
            PongPaddleInputComponent(char up_key, char down_key);

        private:
            void handleMessage(InputMessage msg) override;

            
            std::map<char, bool> m_keys_down;
        };

    }
}

