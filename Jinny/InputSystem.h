#pragma once

#include <vector>
#include <map>
#include <utility>

#include "GameSystem.h"

#include "MessageBoard.h"
#include "InputMessage.h"



// Framework Dependencies
#include "Shape.h"

namespace Framework
{
    class Input;
    enum class MouseEvent;

    class Window;
}

namespace Jinny
{
    class InputSystem : public GameSystem
    {
    public:
        typedef std::pair<int, Framework::Shape*> InputData;

        // Constructor
        InputSystem(const Framework::Window& t_window, const Framework::Input& t_input, MessageBoard<InputMessage>& t_message_board);

        // Update
        void update();

    private:
        // Virtual Overides for update function
        void handleMessages();

        // --- Framework ---
        const Framework::Input& f_input;
        const Framework::Window& f_window;

        // --- Data ---

        // Message Board
        MessageBoard<InputMessage>& m_message_board;

        // Input Subscriptions
        std::map<Framework::MouseEvent, std::vector<InputData>> m_mouse_button_subscriptions;

        std::map<InputData, bool> m_mouse_over_subscribtions;

        std::map<char, std::vector<int>> m_key_supscriptions;
    };
}



