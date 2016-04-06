#include "configuration.hpp"
#include "log.hpp"
#include <fstream>
#include <regex>

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

	bool Configuration::loadConfiguration()
	{
		DataValue temp;

		return temp.loadFile("config.cfg");
	}

}
