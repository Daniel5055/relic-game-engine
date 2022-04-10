#pragma once

#include <vector>
#include <map>
#include <utility>

#include "GameSystem.h"
#include "MessageReceiver.h"
#include "MessageSender.h"
#include "InputType.h"
#include "GameType.h"

// Framework Dependencies
#include "Shape.h"

namespace framework
{
    class Input;
    enum class MouseEvent;

    class Window;
}

namespace relic
{
    /**
     * \brief System responsible for handling inputs and subscribing objects to inputs
     */
    class InputSystem final : 
        public GameSystem,
        public MessageReceiver<InputSystemType>,
        public MessageSender<InputObjectType>,
        public MessageSender<GameSystemType>
    {
    public:
        typedef std::pair<Identifier, framework::Shape*> input_data;

        // Constructor
        InputSystem(const framework::Window& window, const framework::Input& input);
    private:

        void doUpdates() override;
        void handleMessage(Message<InputSystemType> msg) override;

        // --- Framework ---
        const framework::Input& f_input;
        const framework::Window& f_window;

        // --- Data ---

        // Input Subscriptions
        std::map<framework::MouseEvent, std::vector<input_data>> m_mouse_button_subscriptions;
        std::map<input_data, bool> m_mouse_over_subscriptions;
        std::map<char, std::vector<Identifier>> m_key_subscription;
    };
}



