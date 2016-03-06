#include "eventmanager.hpp"
#include "events/event.hpp"
#include "events/eventsender.hpp"
#include "events/eventreceiver.hpp"
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

		sptr<events::EventSender> EventManager::newEventSender()
		{
			auto temp = sptr<events::EventSender>(new events::EventSender(this));
			m_eventsenders.push_back(temp);
			return temp;
		}


		sptr<events::EventReceiver> EventManager::newEventReceiver()
		{
			auto temp = sptr<events::EventReceiver>(new events::EventReceiver(this));
			m_eventreceivers.push_back(temp);
			return temp;
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
				events::EventReceiver::ReceivedEvent &next = m_eventQueue.front();
				for (auto receiver : m_eventreceivers)
				{
					auto receiver_ = receiver.lock();
					if (receiver_)
					{
						receiver_->receive(next);
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