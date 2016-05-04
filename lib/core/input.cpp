#include "input.hpp"
#include "log.hpp"
#include "../draw/scenenode.hpp"
#include "inputreceiver.hpp"
namespace lib
{
	InputData::InputData(const sptr<DataMap> &eventData)
		: m_device{ static_cast<InputData::Device>(eventData->at("Device").getu8()) },
		m_action{ static_cast<InputData::Action>(eventData->at("Action").getu8()) },
		m_key{ static_cast<InputData::Device>(eventData->at("Key").gets32()) }
		{}

	Input::Input() {}

	Input::~Input() {}

	void Input::Init() {}

	void Input::processSystemEvent(const sptr<DataMap> &eventData)
	{
		__ASSERT(eventData, "Map parameter is nullptr");
		m_iData.push_back(InputData{ eventData });
	}
	
	void Input::updateNode(const sptr<draw::SceneNode> &node)
	{
		if (!m_iData.empty()) {
			auto iReceiver = std::dynamic_pointer_cast<InputReceiverNode>(node);

			if (iReceiver) {
				for (const InputData &iData : m_iData) {
					if (iData.action() == InputData::Action::KeyPressed) {
						iReceiver->onKeyPressed(iData.key());
					}
					else {
						iReceiver->onKeyReleased(iData.key());
					}
				}
			}
		}
	}

	void Input::nextFrame()
	{
		reset();
	}

	void Input::reset()
	{
		m_iData.clear();
	}
}
