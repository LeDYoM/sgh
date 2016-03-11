#include "eventproxy.hpp"
#include "../eventmanager.hpp"
#include "event.hpp"
#include "eventsender.hpp"
#include "eventreceiver.hpp"
#include "../log.hpp"

namespace lib
{
	namespace core
	{
		namespace events
		{
			EventProxy::EventProxy(EventManager *const eventManager)
				: m_eventManager{ eventManager }
			{
				LOG_CONSTRUCT_NOPARAMS;
			}

			EventProxy::~EventProxy()
			{
				LOG_DESTRUCT_NOPARAMS;
			}

			sptr<events::EventSender> EventProxy::newEventSender()
			{
				auto temp = sptr<events::EventSender>(new events::EventSender(this));
				m_eventsenders.push_back(temp);
				return temp;
			}

			sptr<events::EventReceiver> EventProxy::newEventReceiver()
			{
				auto temp = sptr<events::EventReceiver>(new events::EventReceiver(this));
				m_eventreceivers.push_back(temp);
				return temp;
			}

			void EventProxy::receive(sptr<Event> ev)
			{
				for (auto receiver : m_eventreceivers)
				{
					auto receiver_ = receiver.lock();
					if (receiver_)
					{
						if (receiver_->isActive())
						{
							receiver_->receive(ev);
						}
					}
				}
			}

			void EventProxy::send(uptr<Event> ev)
			{
				m_eventManager->addEvent(std::move(ev));
			}
		}
	}
}