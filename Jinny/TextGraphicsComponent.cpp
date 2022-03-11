#include "TextGraphicsComponent.h"

Jinny::TextGraphicsComponent::TextGraphicsComponent(std::string text, std::string font_name, Framework::Color font_color, std::string font_path, int font_size)
{
	// Create Graphic
	setGraphic(new Framework::Graphic());

	if (font_path != "")
	{
		GraphicsMessage g_msg_1;
		g_msg_1.type = GMessageType::LOAD_FONT;
		g_msg_1.string_1 = font_name;
		g_msg_1.string_2 = font_path;
		g_msg_1.num = font_size;
		pushMessage(g_msg_1);
	}

	GraphicsMessage g_msg_2;
	g_msg_2.type = GMessageType::ASSIGN_TEXT;
	g_msg_2.string_1 = text;
	g_msg_2.string_2 = font_name;
	g_msg_2.color = font_color;
	g_msg_2.graphic = getGraphic();
	pushMessage(g_msg_2);
}

void Jinny::TextGraphicsComponent::initialize(GameObject& object)
{
	// Set Object
	setObject(&object);

	// Recieve Object shape
	ObjectEvent o_event = *object.getQueueIterator();
	if (o_event.type == EventType::OBJECT_INITIALIZATION_SHAPE)
	{
		getGraphic()->setShape(o_event.shape);
	}

	GraphicsMessage g_msg;
	g_msg.type = GMessageType::SHOW_GRAPHIC;
	g_msg.object_ID = object.getObjectID();
	g_msg.graphic = getGraphic();
	pushMessage(g_msg);
}
