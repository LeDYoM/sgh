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
	using InputReceiverCallback = std::function<void(Node *node, const InputData &iData)>;

	class InputReceiver
	{
	public:
		InputReceiver(Node *obj, InputReceiverCallback callback)
			: m_node{ obj }, m_callback{ callback } {}

	private:
		InputReceiverCallback m_callback{ nullptr };
		Node *m_node;
	};

	class Input : public AppService
	{
	public:
		Input();
		virtual ~Input();
		static const str staticTypeName() { return "Input"; }
		void Init() override;

		void processSystemEvent(const sptr<DataMap> eventData);
		void addInputCallback(Node *node, InputReceiverCallback callback);
	private:
	};
}

#endif
