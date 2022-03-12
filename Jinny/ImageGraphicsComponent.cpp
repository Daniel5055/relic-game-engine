#include "ImageGraphicsComponent.h"

Jinny::ImageGraphicsComponent::ImageGraphicsComponent(std::string texture_name, std::string texture_path)
{
	// Create Graphic
	setGraphic(new Framework::Graphic());

	// If texture path not provided then send a message to load the texutre from the path
	if (texture_path != "")
	{
		GraphicsMessage g_msg_1;
		g_msg_1.type = GMessageType::LOAD_TEXTURE;
		g_msg_1.string_1 = texture_name;
		g_msg_1.string_2 = texture_path;
		pushMessage(g_msg_1);
	}

	// Then send a message to assign the texture to the graphic
	GraphicsMessage g_msg_2;
	g_msg_2.type = GMessageType::ASSIGN_TEXTURE;
	g_msg_2.string_1 = texture_name;
	g_msg_2.graphic = getGraphic();
	pushMessage(g_msg_2);
}

void Jinny::ImageGraphicsComponent::initialize(GameObject& object)
{
	// Set Object
	setObject(&object);
	Framework::Graphic* g = getGraphic();

	// Recieve Object shape
	for (auto it = object.getQueueIterator(); it != object.getQueueEnd(); it++)
	{
		switch (it->type)
		{
		case EventType::OBJECT_INITIALIZATION_SHAPE:
			getGraphic()->setShape(it->shape);
		}
	}

	GraphicsMessage g_msg;
	g_msg.type = GMessageType::SHOW_GRAPHIC;
	g_msg.object_ID = object.getObjectID();
	g_msg.graphic = getGraphic();
	pushMessage(g_msg);
}