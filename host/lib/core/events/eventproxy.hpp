#ifndef LIB_EVENTPROXY_HPP__
#define LIB_EVENTPROXY_HPP__

#include <lib/include/types.hpp>
#include <queue>
#include <functional>

namespace lib
{
	namespace core
	{
		class EventManager;

		namespace events
		{
			class EventSender;
			class EventReceiver;
			class Event;

			class EventProxy
			{
			public:
				EventProxy(EventManager *const eventManager);
				virtual ~EventProxy();

				sptr<events::EventSender> newEventSender();
				sptr<events::EventReceiver> newEventReceiver();
				void receive(sptr<Event> ev);
				void send(uptr<Event> ev);
			private:
				std::vector<wptr<events::EventSender>> m_eventsenders;
				std::vector<wptr<events::EventReceiver>> m_eventreceivers;
				EventManager *const m_eventManager;
			};
		}
	}
}
#endif
