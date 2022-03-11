#pragma once

// Using a queue as these types of messanger are only between two systems
// And messages will only be popped for length of queue
// So messages may be pushed while message handling
#include <queue>

namespace Jinny
{
	// Messages get pushed up
	// And Messages get popped out

	// Template Messageboard
	template<typename Message>
	class MessageBoard
	{
	public:

		void pushMessage(Message msg)
		{
			m_message_queue.push(msg);
		}

		Message popMessage()
		{

			// Should not be any error as systems should know how much to pop
			Message msg = m_message_queue.front();
			m_message_queue.pop();
			return msg;
		}

		int getQueueSize()
		{
			return m_message_queue.size();
		}

	private:
		// General 
		std::queue<Message> m_message_queue;
	};

}