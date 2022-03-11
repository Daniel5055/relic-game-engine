#pragma once

#include "Component.h"
#include "GameMessage.h"
#include "MessageBoard.h"

namespace Jinny
{

	class CoreComponent : public Component
	{
	public:
		// --- virtual functions ---
		// Initialization
		virtual void initialize(GameObject& object);

		// Updating
		virtual void update();

		// Closing
		virtual void close();

		// --- static functions ---

		// Functions to be used by object
		void recieveMessage(GameMessage c_msg);

		// To set messageBoard
		static void setMessageBoard(MessageBoard<GameMessage>* message_board);

	protected:
		// --- inherited functions ---

		// Pops Message from queue
		GameMessage popMessage();

		// --- inherited virtual functions ---

		// Event Handling
		virtual void handleEvents();

		// Message Handling
		virtual void handleMessages();

		// Message Pushing
		void pushMessage(GameMessage g_msg);

	private:

		// --- Data ---

		// Message Queue
		std::queue<GameMessage> m_message_queue;

		// Access to message board
		static MessageBoard<GameMessage>* m_message_board;
	};
}