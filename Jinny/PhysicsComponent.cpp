#include "PhysicsComponent.h"

#include "PhysicsMessage.h"

Jinny::MessageBoard<Jinny::PhysicsMessage>* Jinny::PhysicsComponent::m_message_board = nullptr;

void Jinny::PhysicsComponent::initialize(GameObject& object)
{
}

void Jinny::PhysicsComponent::update()
{
}

void Jinny::PhysicsComponent::close()
{
}

void Jinny::PhysicsComponent::recieveMessage(PhysicsMessage p_msg)
{
	m_message_queue.push(p_msg);
}

Jinny::PhysicsMessage Jinny::PhysicsComponent::popMessage()
{
	PhysicsMessage msg;

	if (m_message_queue.size() > 0)
	{
		msg = m_message_queue.front();
		m_message_queue.pop();

	}
	else
	{
		msg.type = PMessageType::NULL_MESSAGE;
	}

	return msg;
}

void Jinny::PhysicsComponent::handleEvents()
{
}

void Jinny::PhysicsComponent::handleMessages()
{
}

void Jinny::PhysicsComponent::pushMessage(PhysicsMessage p_msg)
{
	m_message_board->pushMessage(p_msg);
}

void Jinny::PhysicsComponent::setMessageBoard(MessageBoard<PhysicsMessage>* message_board)
{
	m_message_board = message_board;
}
