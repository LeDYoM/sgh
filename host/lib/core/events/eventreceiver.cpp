#include "eventreceiver.hpp"
#include "../eventmanager.hpp"

namespace lib
{
	namespace core
	{
		namespace events
		{
			EventReceiver::EventReceiver(EventManager *const eventManager) : m_eventManager{ eventManager }
			{

			}


			void EventReceiver::receive(ReceivedEvent event_)
			{
				if (m_listener)
				{
					m_listener(event_);
				}
			}

			EventReceiver::~EventReceiver()
			{

			}

			void EventReceiver::setReceiver(EventListener listener)
			{
				m_listener = listener;
			}

		}
	}
}
