#pragma once

#include <vector>
#include <map>
#include <utility>

#include "GameSystem.h"
#include "MessageReceiver.h"
#include "MessageSender.h"
#include "InputMessage.h"

// Framework Dependencies
#include "Shape.h"

namespace framework
{
    class Input;
    enum class MouseEvent;

    class Window;
}

namespace jinny
{
    /**
     * \brief System responsible for handling inputs and subscribing objects to inputs
     */
    class InputSystem final : 
        public GameSystem,
        public MessageReceiver<InputMessage>,
        public MessageSender<InputMessage>
    {
    public:
        typedef std::pair<int, framework::Shape*> input_data;

        // Constructor
        InputSystem(const framework::Window& window, const framework::Input& input);
    private:

        void doUpdates() override;
        void handleMessage(InputMessage msg) override;

        // --- Framework ---
        const framework::Input& f_input;
        const framework::Window& f_window;

        // --- Data ---

        // Input Subscriptions
        std::map<framework::MouseEvent, std::vector<input_data>> m_mouse_button_subscriptions;
        std::map<input_data, bool> m_mouse_over_subscriptions;
        std::map<char, std::vector<int>> m_key_subscription;
    };
}



