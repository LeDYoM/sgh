#include "input.hpp"
#include "log.hpp"

namespace lib
{
	InputData::InputData(const sptr<DataMap> eventData)
		: m_device{ static_cast<InputData::Device>(eventData->at("Device").getu8()) },
		m_action{ static_cast<InputData::Action>(eventData->at("Action").getu8()) },
		m_key{ static_cast<InputData::Device>(eventData->at("Key").gets32()) }
		{}

	Input::Input() {}

	Input::~Input() {}

	void Input::Init() {}

	void Input::processSystemEvent(const sptr<DataMap> eventData)
	{
		__ASSERT(eventData, "Map parameter is nullptr");
	}
}
