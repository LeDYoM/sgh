#ifndef LIB__INPUT_HPP__
#define LIB__INPUT_HPP__

#include <lib/include/types.hpp>
#include <lib/include/key.hpp>
#include "appservice.hpp"
#include "datamap.hpp"
#include <stack>

namespace lib
{
	namespace draw
	{
		class SceneNode;
	}
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

		InputData(const sptr<DataMap> &eventData);
		InputData &operator=(const InputData&) = delete;
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

		void processSystemEvent(const sptr<DataMap> &eventData);
		void updateNode(const sptr<draw::SceneNode>&);
		void nextFrame();
		void reset();
	private:
		std::vector<InputData> m_iData;
	};
}

#endif
