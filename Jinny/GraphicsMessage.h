#pragma once

#include <string>
#include "Color.h"
namespace Framework
{
	class Graphic;
}
namespace Jinny
{
	enum class GMessageType
	{
		NULL_MESSAGE = 0,

		LOAD_TEXTURE,
		LOAD_FONT,
		ASSIGN_TEXTURE,
		ASSIGN_TEXT,

		SHOW_GRAPHIC,
		HIDE_GRAPHIC,
	};

	struct GraphicsMessage
	{
		GraphicsMessage(GMessageType msg_type = GMessageType::NULL_MESSAGE, int id = -1)
		{
			type = msg_type;
			object_ID = id;
		}

		GMessageType type;
		int object_ID;

		Framework::Graphic* graphic;

		std::string string_1;
		std::string string_2;
		int num;
		Framework::Color color;
	};
}