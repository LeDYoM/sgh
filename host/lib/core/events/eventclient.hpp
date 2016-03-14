#ifndef LIB_EVENTCLIENT_HPP__
#define LIB_EVENTCLIENT_HPP__

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
			class Event;

			class EventClient
			{
			public:
				typedef sptr<Event> ReceivedEvent;
				typedef std::function<void(ReceivedEvent)> EventListener;

				EventClient(EventManager *const eventManager);
				virtual ~EventClient();

				EventClient &operator=(EventClient &r) = delete;

				void receive(ReceivedEvent ev);
				void send(uptr<Event> ev);
				void setReceiver(EventListener listener);

				void setActive(bool active);
				const  bool isActive() const;
				sptr<EventClient> newEventClient();
			private:
				EventManager *const m_eventManager;
				std::vector <wptr<EventClient>> m_eventClients;
				EventListener m_listener{ nullptr };
				bool m_active{ true };
			};
		}
	}
}
#endif
