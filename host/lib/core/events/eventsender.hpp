#ifndef __LIB_CORE_EVENTSENDER_HPP__
#define __LIB_CORE_EVENTSENDER_HPP__

#include "event.hpp"
#include <lib/include/types.hpp>

namespace lib
{
	namespace core
	{
		namespace events
		{
			class EventProxy;
			class EventSender
			{
			public:
				EventSender &operator=(const EventSender &rh) = delete;
				virtual ~EventSender();

				virtual void sendEvent(uptr<events::Event> event_);
			private:
				EventSender(EventProxy *const eventProxy);
				EventProxy  *const m_eventProxy;
				friend class EventProxy;
			};
		}
	}
}
#endif
