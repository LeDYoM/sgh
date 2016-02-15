#ifndef __LIB_EVENT_INPUTEVENT_HPP__
#define __LIB_EVENT_INPUTEVENT_HPP__

#include <lib/include/key.hpp>
#include "event.hpp"

namespace lib
{
	namespace core
	{
		namespace events
		{
			class InputEvent : public Event
			{
			public:
				enum class Device
				{
					Keyboard
				};
				virtual EventType eventType() { return Event::EventType::Input; }
				InputEvent(const Device &device_) : m_device{ device_ } {}
			private:
				const Device m_device;
			};

			class KeyEvent : public InputEvent
			{
			public:
				enum class Action
				{
					KeyPressed,
					KeyReleased
				};

				KeyEvent(const Action action_, const input::Key key) : InputEvent{ Device::Keyboard }, m_action{ action_ }, m_key{ key } {}
				const Action &action() const { return m_action; }
				const input::Key &key() const { return m_key; }
			private:
				const Action m_action;
				const input::Key m_key;
			};
		}
	}
}

#endif
