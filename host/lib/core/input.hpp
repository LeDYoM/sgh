#ifndef LIB__INPUT_HPP__
#define LIB__INPUT_HPP__

#include <lib/include/types.hpp>
#include <lib/include/key.hpp>
#include "appservice.hpp"
#include "data.hpp"

namespace lib
{
	class InputData
	{
	public:
		enum Device
		{
			Keyboard
		};
		enum Action
		{
			KeyPressed,
			KeyReleased
		};

		const Action &action() const { return m_action; }
		const Key &key() const { return m_key; }

	private:
		const Device m_device;
		const Key m_key;
		const Action m_action;
	};

	class Input : public AppService
	{
	public:
		Input();
		virtual ~Input();
		static const str staticTypeName() { return "Input"; }
		void Init() override;

		void addInputAction(const sptr<DataMap> eventData);
	};
}

#endif
