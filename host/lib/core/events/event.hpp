#ifndef __LIB_EVENT_HPP__
#define __LIB_EVENT_HPP__

#include <lib/include/types.hpp>

namespace lib
{
	namespace core
	{
		namespace events
		{
			class Event
			{
			public:
				enum class EventType
				{
					Unknown,
					Input
				};
				Event() {}
				Event &operator=(const Event &rho) = delete;
				virtual ~Event() {}
				virtual EventType eventType() = 0;
			};
			template <class T>
			sptr<T> getEventAs(sptr<Event> event_)
			{
				return std::dynamic_pointer_cast<T>(event_);
			}

		}
	}
}
#endif
