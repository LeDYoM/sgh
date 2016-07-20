#ifndef __LIB_PARAMPARSER_HPP__
#define __LIB_PARAMPARSER_HPP__

#include <lib/include/types.hpp>
#include "data.hpp"

namespace lib
{
	class ParamParser
	{
	public:
		ParamParser(int argc, char *argv[]);
		virtual ~ParamParser();

	private:
		std::vector<std::string> m_params;
		DataMap m_parsedParams;
	};
}

#endif
