#include "paramparser.hpp"
#include "log.hpp"
#include <algorithm>
#include "strutils.hpp"
#include "datamap.hpp"

#define LOG_PPARSER(x) LOG_DEBUG("PARAMPARSER: "<<x)

namespace lib
{
	namespace core
	{
		namespace priv
		{
			struct ParamParserPrivate
			{
				std::vector<std::string> m_params;
				DataMap m_parsedParams;
			};
		}

		ParamParser::ParamParser(int argc, char *argv[])
			: priv{ new priv::ParamParserPrivate() }
		{
			auto &m_params(priv->m_params);
			m_params.clear();
			for (auto i = 1; i < argc; ++i)
			{
				m_params.push_back(argv[i]);
			}

			m_params.push_back("-rx=800");
			m_params.push_back("-ry=600");

			std::for_each(m_params.cbegin(), m_params.cend(), [](const str&element) {LOG_DEBUG(element)});
			for (std::string &element : m_params)
			{
				if (starts_with(element, "-"))
				{
					element = element.substr(1);
				}
			}
			std::for_each(m_params.cbegin(), m_params.cend(), [](const str&element) {LOG_DEBUG(element)});

			u32 count{};
			priv->m_parsedParams = std::move(DataValue::fromStringVector(m_params, count));
			LOG_DEBUG(DataValue{ priv->m_parsedParams });
		}

		ParamParser::~ParamParser()
		{
			delete priv;
		}
	}
}
