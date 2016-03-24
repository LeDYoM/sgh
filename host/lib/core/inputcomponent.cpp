#include "eventmanager.hpp"
#include "events/event.hpp"
#include "events/eventclient.hpp"
#include "log.hpp"

namespace lib
{
	namespace core
	{

		EventManager::EventManager()
		{
			LOG_CONSTRUCT_NOPARAMS;
		}

		EventManager::~EventManager()
		{
			LOG_DEBUG("Going to destroy event manager...");
			while (!m_eventQueue.empty())
			{
				LOG_DEBUG("Event was still in queue: " << typeid(m_eventQueue.front()).name());
				m_eventQueue.pop();
			}
			LOG_DESTRUCT_NOPARAMS;
		}

		sptr<events::EventClient> EventManager::newEventClient()
		{
			auto ep = sptr<events::EventClient>(new events::EventClient{ this });
			m_eventClients.push_back(ep);
			return ep;
		}

		void EventManager::addEvent(uptr<events::Event> event_)
		{
			m_eventQueue.push(std::move(event_));
		}

		void EventManager::update()
		{
			while (!empty())
			{
				update1();
			}
		}

		void EventManager::update1()
		{
			if (!m_eventQueue.empty())
			{
				events::EventClient::ReceivedEvent &next = m_eventQueue.front();
				for (auto eproxy : m_eventClients)
				{
					auto eproxy_ = eproxy.lock();
					if (eproxy_)
					{
						eproxy_->receive(next);
					}
					else
					{
						//TO DO: Delete proxy from list
					}
				}
				m_eventQueue.pop();
			}
		}


		lib::u32 EventManager::pendingEvents()
		{
			return m_eventQueue.size();
		}

		bool EventManager::empty()
		{
			return m_eventQueue.empty();
		}
	}
}