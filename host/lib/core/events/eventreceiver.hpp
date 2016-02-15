#ifndef __LIB_CORE_EVENTRECEIVER_HPP__
#define __LIB_CORE_EVENTRECEIVER_HPP__

#include "event.hpp"
#include <functional>
#include <lib/include/types.hpp>

namespace lib
{
	namespace core
	{
		class EventManager;

		namespace events
		{
			class EventReceiver
			{
			public:
				typedef sptr<Event> ReceivedEvent;
				typedef std::function<void(ReceivedEvent)> EventListener;
				EventReceiver &operator=(const EventReceiver &rh) = delete;
				virtual ~EventReceiver();

				void setReceiver(EventListener listener);

			private:
				EventReceiver(EventManager *const eventManager);
				void receive(ReceivedEvent event_);
				EventManager  *const m_eventManager;
				EventListener m_listener;
				friend class EventManager;
			};
		}
	}
}
#endif
