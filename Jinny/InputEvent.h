#pragma once

namespace Framework
{
	enum class InputEventType
	{
		NULL_EVENT = 0,

		EXIT_BUTTON_PRESSED,

		MOUSE_EVENT,
		SCROLL_WHEEL,

		KEY_DOWN,
		KEY_UP,
	};

	enum class MouseEvent
	{
		MOUSE_MOTION,

		// ID nums notably ressemble objectInput equivalents
		LEFT_DOWN = 8,
		LEFT_UP = 9,
		RIGHT_DOWN = 10,
		RIGHT_UP = 11,

	};

	struct InputEvent
	{
		InputEventType type;

		union
		{
			char key;
			MouseEvent mouse_event;
			short scroll_wheel;
		};
		
	};
}