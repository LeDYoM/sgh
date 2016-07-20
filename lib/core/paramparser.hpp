#ifndef LIB_PARAMPARSER_HPP__
#define LIB_PARAMPARSER_HPP__

#include <lib/include/types.hpp>
#include <lib/include/compconfig.hpp>

namespace lib
{
	namespace priv
	{
		struct ParamParserPrivate;
	}
	class LIB_API ParamParser
	{
	public:
		ParamParser(int argc, char *argv[]);
		virtual ~ParamParser();
	private:
		priv::ParamParserPrivate *priv;
	};
}

#endif
