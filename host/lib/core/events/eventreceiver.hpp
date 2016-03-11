#ifndef __LIB_CORE_EVENTRECEIVER_HPP__
#define __LIB_CORE_EVENTRECEIVER_HPP__

#include "event.hpp"
#include <functional>
#include <lib/include/types.hpp>

namespace lib
{
	namespace core
	{
		namespace events
		{
			class EventProxy;
			class EventReceiver
			{
			public:
				typedef sptr<Event> ReceivedEvent;
				typedef std::function<void(ReceivedEvent)> EventListener;
				EventReceiver &operator=(const EventReceiver &rh) = delete;
				virtual ~EventReceiver();

				void setReceiver(EventListener listener);
				void setActive(bool active);
				const  bool isActive() const;

			private:
				EventReceiver(EventProxy *const eventProxy);
				void receive(ReceivedEvent event_);
				EventProxy  *const m_eventProxy;
				EventListener m_listener;
				bool m_active{ false };
				friend class EventProxy;
			};
		}
	}
}
#endif
