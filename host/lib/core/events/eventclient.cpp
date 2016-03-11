#include "eventclient.hpp"
#include "../eventmanager.hpp"
#include "event.hpp"
#include "../log.hpp"

namespace lib
{
	namespace core
	{
		namespace events
		{
			EventClient::EventClient(EventManager *const eventManager)
				: m_eventManager{ eventManager }
			{
				LOG_CONSTRUCT_NOPARAMS;
			}

			EventClient::~EventClient()
			{
				LOG_DESTRUCT_NOPARAMS;
			}

			void EventClient::receive(ReceivedEvent ev)
			{
				if (m_active)
				{
					if (m_listener)
					{
						m_listener(ev);
					}
					for (auto client : m_eventClients)
					{
						auto client_ = client.lock();
						if (client_)
						{
							if (client_->isActive())
							{
								client_->receive(ev);
							}
						}
					}
				}
			}

			void EventClient::setActive(bool active)
			{
				m_active = active;
			}

			const bool EventClient::isActive() const
			{
				return m_active;
			}

			sptr<EventClient> EventClient::newEventClient()
			{
				auto ep = sptr<events::EventClient>(new events::EventClient{ m_eventManager });
				m_eventClients.push_back(ep);
				return ep;
			}

			void EventClient::send(uptr<Event> ev)
			{
				m_eventManager->addEvent(std::move(ev));
			}

			void EventClient::setReceiver(EventListener listener)
			{
				m_listener = listener;
			}

		}
	}
}
