#pragma once


#include "Component.h"

#include "InputMessage.h"
#include "MessageBoard.h"



namespace Jinny
{

	class InputComponent : public Component
	{
	public:

		// --- pure virtual functions ---

		// Initialization
		virtual void initialize(GameObject& object);

		// Updating
		virtual void update();

		// Closing
		virtual void close();

		// --- functions ---

		// For Object to relay message to input
		void recieveMessage(InputMessage i_msg);

		// To set messageBoard
		static void setMessageBoard(MessageBoard<InputMessage>* message_board);

	protected:
		// --- inherited functions ---

		// Pops Message from queue
		InputMessage popMessage();

		// --- inherited virtual functions ---

		// Event Handling
		virtual void handleEvents();

		// Message Handling
		virtual void handleMessages();

		// Message Pushing
		void pushMessage(InputMessage i_msg);
	private:

		// --- Data ---

		// Message Queue
		std::queue<InputMessage> m_message_queue;

		// Access to message board
		static MessageBoard<InputMessage>* m_message_board;
	};
}


