#include "CoreComponent.h"

#include "CoreMessage.h"

Jinny::MessageBoard<Jinny::GameMessage>* Jinny::CoreComponent::m_message_board = nullptr;

void Jinny::CoreComponent::initialize(GameObject& object)
{
	setObject(&object);
}

void Jinny::CoreComponent::update()
{
}

void Jinny::CoreComponent::close()
{
}

void Jinny::CoreComponent::recieveMessage(GameMessage g_msg)
{
	m_message_queue.push(g_msg);
}

void Jinny::CoreComponent::setMessageBoard(MessageBoard<GameMessage>* message_board)
{
	m_message_board = message_board;
}

Jinny::GameMessage Jinny::CoreComponent::popMessage()
{
	GameMessage msg;

	if (m_message_queue.size() > 0)
	{
		msg = m_message_queue.front();
		m_message_queue.pop();

	}
	else
	{
		msg.type = GameMessageType::NULL_MESSAGE;
	}

	return msg;
}

void Jinny::CoreComponent::handleEvents()
{
}

void Jinny::CoreComponent::handleMessages()
{
}

void Jinny::CoreComponent::pushMessage(GameMessage c_msg)
{
	m_message_board->pushMessage(c_msg);
}