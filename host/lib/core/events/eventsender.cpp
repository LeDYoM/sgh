#include "eventsender.hpp"
#include "eventproxy.hpp"

namespace lib
{
	namespace core
	{
		namespace events
		{
			EventSender::EventSender(EventProxy *const eventProxy) : m_eventProxy{ eventProxy }
			{

			}

			EventSender::~EventSender()
			{

			}

			void EventSender::sendEvent(uptr<events::Event> event_)
			{
				m_eventProxy->send(std::move(event_));
			}

		}
	}
}
