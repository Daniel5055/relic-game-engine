#pragma once

namespace framework
{
    enum class InputEventType
    {
        null_event = 0,

        exit_button_pressed,

        mouse_event,
        scroll_wheel,

        key_down,
        key_up,
    };

    enum class MouseEvent
    {
        mouse_motion,

        // ID nums notably ressemble objectInput equivalents
        left_down = 8,
        left_up = 9,
        right_down = 10,
        right_up = 11,

    };

    /**
     * Simple struct to contain information about an input event.
     */
    struct InputEvent
    {
        InputEventType type;

        // Union used to conserve memory
        union
        {
            char key;
            MouseEvent mouse_event;
            short scroll_wheel;
        };

    };
}