#ifndef LIB__INPUT_HPP__
#define LIB__INPUT_HPP__

#include <lib/include/types.hpp>
#include <lib/include/key.hpp>
#include "appservice.hpp"
#include "data.hpp"
#include <stack>

namespace lib
{
	class InputData
	{
	public:
		enum Device : u8
		{
			Keyboard = 0,
		};
		enum Action : u8
		{
			KeyPressed=0,
			KeyReleased=1
		};

		const Device &device() const { return m_device; }
		const Action &action() const { return m_action; }
		const Key &key() const { return m_key; }

		InputData(const sptr<DataMap> eventData);
	private:
		const Device m_device;
		const Key m_key;
		const Action m_action;
	};

	class Node;

	class Receiver
	{

	};
	class KeyPressedReceiver : public Receiver
	{
	public:
		KeyPressedReceiver() {}
		virtual ~KeyPressedReceiver() {}
		
		virtual void onKeyPressed(const Key &key) = 0;
	};

	class KeyReleasedReceiver : public Receiver
	{
	public:
		KeyReleasedReceiver() {}
		virtual ~KeyReleasedReceiver() {}
		
		virtual void onKeyReleased(const Key &key) = 0;
	};

	class Input : public AppService
	{
	public:
		Input();
		virtual ~Input();
		static const str staticTypeName() { return "Input"; }
		void Init() override;

		void processSystemEvent(const sptr<DataMap> eventData);
		void updateNode(const sptr<Node>);
	private:
		std::stack<InputData> m_iData;
	};
}

#endif
