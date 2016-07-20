#include "paramparser.hpp"
#include "log.hpp"
#include <algorithm>
#include "strutils.hpp"
#include "data.hpp"

#define LOG_PPARSER(x) LOG_DEBUG("PARAMPARSER: "<<x)

namespace lib
{
	ParamParser::ParamParser(int argc, char *argv[])
	{
		m_params.clear();
		for (int i = 1; i<argc; ++i)
		{
			m_params.push_back(argv[i]);
		}

		std::for_each(m_params.cbegin(), m_params.cend(), [](const std::string&element){LOG_DEBUG(element)});
		for (std::string &element : m_params)
		{
			if (starts_with(element, "-"))
			{
				element = element.substr(1);
			}
		}
		std::for_each(m_params.begin(), m_params.end(), [](std::string&element){LOG_DEBUG(element)});

		u32 count{};
		m_parsedParams = std::move(DataValue::fromStringVector(m_params, count));
	}

	ParamParser::~ParamParser()
	{
	}
}
