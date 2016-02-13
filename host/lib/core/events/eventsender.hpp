#ifndef __LIB_CORE_EVENTSENDER_HPP__
#define __LIB_CORE_EVENTSENDER_HPP__

#include "event.hpp"

namespace lib
{
	namespace core
	{
		class EventManager;

		namespace events
		{
			class EventSender
			{
			public:
				EventSender &operator=(const EventSender &rh) = delete;
				virtual ~EventSender();

				virtual void sendEvent(uptr<lib::events::Event> event_);
			private:
				EventSender(EventManager *const eventManager);
				EventManager  *const m_eventManager;
				friend class EventManager;
			};
		}
	}
}
#endif
