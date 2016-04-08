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
		std::vector<str> data(loadFile("config.cfg"));
		u32 count{ 0 };
		DataMap temp = DataValue::fromStringVector(data,count);
		return true;
	}

	std::vector<str> Configuration::loadFile(const std::string &file)
	{
		LOG_DEBUG("Trying to read file " + file);
		std::vector<str> data;
		std::ifstream f(file);

		if (f.is_open())
		{
			while (f)
			{
				str line;
				f >> line;
				data.push_back(line);
			}
		}
		return data;
	}
}
