#include "eventreceiver.hpp"
#include "eventproxy.hpp"

namespace lib
{
	namespace core
	{
		namespace events
		{
			EventReceiver::EventReceiver(EventProxy *const eventProxy) : m_eventProxy{ eventProxy }
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
