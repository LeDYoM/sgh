#ifndef LIB_PARAMPARSER_HPP__
#define LIB_PARAMPARSER_HPP__

#include <lib/include/types.hpp>
#include <lib/include/compconfig.hpp>

namespace lib
{
	class DataMap;
	namespace core
	{
		namespace priv
		{
			struct ParamParserPrivate;
		}
		class ParamParser
		{
		public:
			ParamParser(int argc, char *argv[]);
			virtual ~ParamParser();

			const DataMap &parameters() const;

		private:
			priv::ParamParserPrivate *priv;
		};
	}
}

#endif
