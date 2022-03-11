#include "GraphicsComponent.h"

#include "GraphicsMessage.h"

Jinny::MessageBoard<Jinny::GraphicsMessage>* Jinny::GraphicsComponent::m_message_board = nullptr;

Jinny::GraphicsComponent::GraphicsComponent()
{
	m_graphic_ptr = nullptr;
}

void Jinny::GraphicsComponent::initialize(GameObject& object)
{
}

void Jinny::GraphicsComponent::update()
{
}

void Jinny::GraphicsComponent::close()
{
	
}

Jinny::GraphicsComponent::~GraphicsComponent()
{
	delete m_graphic_ptr;
	m_graphic_ptr = nullptr;
}

void Jinny::GraphicsComponent::recieveMessage(GraphicsMessage g_msg)
{
	m_message_queue.push(g_msg);
}

void Jinny::GraphicsComponent::setMessageBoard(MessageBoard<GraphicsMessage>* message_board)
{
	m_message_board = message_board;
}

void Jinny::GraphicsComponent::setClipPtr(Framework::Shape* clip)
{
	m_graphic_ptr->setClip(clip);
}

Jinny::GraphicsMessage Jinny::GraphicsComponent::popMessage()
{
	GraphicsMessage msg;

	if (m_message_queue.size() > 0)
	{
		msg = m_message_queue.front();
		m_message_queue.pop();

	}
	else
	{
		msg.type = GMessageType::NULL_MESSAGE;
	}

	return msg;
}

Framework::Graphic* Jinny::GraphicsComponent::getGraphic()
{
	return m_graphic_ptr;
}

void Jinny::GraphicsComponent::setGraphic(Framework::Graphic* graphic_ptr)
{
	m_graphic_ptr = graphic_ptr;
}

void Jinny::GraphicsComponent::handleEvents()
{
}

void Jinny::GraphicsComponent::handleMessages()
{
}

void Jinny::GraphicsComponent::pushMessage(GraphicsMessage g_msg)
{
	m_message_board->pushMessage(g_msg);
}
