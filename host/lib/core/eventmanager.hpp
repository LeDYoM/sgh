#ifndef __LIB_EVENTMANAGER_HPP__
#define __LIB_EVENTMANAGER_HPP__

#include "appservice.hpp"
#include <lib/include/types.hpp>
#include "vecsptr.hpp"
#include <queue>
#include <functional>

namespace lib
{
	namespace core
	{
		namespace events
		{
			class Event;
			class EventClient;
		}
		class EventManager : public AppService
		{
		public:
			EventManager();
			virtual ~EventManager();

			sptr<events::EventClient> newEventClient();
			virtual void addEvent(uptr<events::Event> event_);
			void update();
			void update1();
			u32 pendingEvents();
			const std::string serviceName() override { return "EventManager"; }

		private:
			virtual bool empty();

			std::queue<sptr<events::Event>> m_eventQueue;
			std::vector<wptr<events::EventClient>> m_eventClients;
		};
	}
}
#endif
