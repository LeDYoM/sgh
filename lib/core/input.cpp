#include "input.hpp"
#include "log.hpp"

namespace lib
{
	Input::Input()
	{

	}

	Input::~Input()
	{

	}

	void Input::Init()
	{

	}

	void Input::addInputAction(const sptr<DataMap> eventData)
	{
		__ASSERT(eventData, "Map parameter is nullptr");

		InputData::Device device{ static_cast<InputData::Device>(eventData->at("Device").getu8()) };
//		InputData::Action action{ static_cast<InputData::Action>(eventData->at("Action").getbool() ? InputData::Action::KeyPressed : InputData::Action::KeyReleased) };
		Key key{ static_cast<InputData::Device>(eventData->at("Key").gets32()) };

	}
}
