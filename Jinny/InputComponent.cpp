#include "InputComponent.h"

#include "ObjectInput.h"
#include "InputMessage.h"


Jinny::MessageBoard<Jinny::InputMessage>* Jinny::InputComponent::m_message_board = nullptr;

void Jinny::InputComponent::initialize(GameObject& object)
{
}

void Jinny::InputComponent::update()
{
}

void Jinny::InputComponent::close()
{
}

void Jinny::InputComponent::recieveMessage(InputMessage i_msg)
{
	m_message_queue.push(i_msg);
}

void Jinny::InputComponent::setMessageBoard(MessageBoard<InputMessage>* message_board)
{
	m_message_board = message_board;
}

Jinny::InputMessage Jinny::InputComponent::popMessage()
{
	InputMessage msg;

	if (m_message_queue.size() > 0)
	{
		msg = m_message_queue.front();
		m_message_queue.pop();

	}
	else
	{
		msg.type = IMessageType::NULL_MESSAGE;
	}

	return msg;
}

void Jinny::InputComponent::handleEvents()
{
}

void Jinny::InputComponent::handleMessages()
{
	
}

void Jinny::InputComponent::pushMessage(InputMessage i_msg)
{
	m_message_board->pushMessage(i_msg);
}
