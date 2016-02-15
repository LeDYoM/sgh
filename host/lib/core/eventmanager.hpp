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
			class EventSender;
			class EventReceiver;
			class Event;
		}
		class EventManager : public AppService
		{
		public:
			EventManager(AppController *const appController);
			virtual ~EventManager();

			sptr<events::EventSender> newEventSender();
			sptr<events::EventReceiver> newEventReceiver();
			virtual void addEvent(uptr<events::Event> event_);
			void update();
			void update1();
			u32 pendingEvents();
		private:
			virtual bool empty();

			std::queue<sptr<events::Event>> m_eventQueue;
			std::vector<wptr<events::EventSender>> m_eventsenders;
			std::vector<wptr<events::EventReceiver>> m_eventreceivers;

		};
	}
}
#endif
