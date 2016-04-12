#include "configuration.hpp"
#include "appcontroller.hpp"
#include "filesystem.hpp"
#include "log.hpp"

namespace lib
{
	Configuration::Configuration()
	{
	}

	Configuration::~Configuration()
	{
	}

	DataMap *Configuration::configuration()
	{
		return m_rootNode["configuration"].getMap();
	}

	DataMap *Configuration::sharedData()
	{
		return m_rootNode["sharedData"].getMap();
	}

	void Configuration::Init()
	{
		std::vector<str> data(service<FileSystem>()->getFile("config.cfg"));
		u32 count{ 0 };
		m_rootNode["configuration"] = std::move(DataValue::fromStringVector(data, count) );
		m_rootNode["sharedData"] = DataMap{};
	}
}
