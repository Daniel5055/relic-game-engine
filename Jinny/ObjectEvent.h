#pragma once

#include "ObjectInput.h"

// Framework Dependencies
namespace Framework
{
	struct Shape;
}

namespace Jinny
{

	enum class EventType
	{
		OBJECT_INITIALIZATION_SHAPE,
		INPUT_TRIGGERED,
	};

	struct ObjectEvent
	{
		ObjectEvent(EventType t)
		{
			type = t;
		}

		ObjectEvent(EventType t, Framework::Shape* s)
		{
			type = t;
			shape = s;

		}

		EventType type;

		union
		{
			Framework::Shape* shape;
			ObjectInput input;
		};
		

		// More?
	};
}


