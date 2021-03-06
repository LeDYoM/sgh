#ifndef LIB_PARAMPARSER_HPP__
#define LIB_PARAMPARSER_HPP__

#include <lib/include/types.hpp>
#include <lib/include/compconfig.hpp>

namespace lib
{
	class DataMap;
	class DataValue;
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
			bool paramEntered(const str&) const;
			const DataValue &param(const str&, const DataValue &defaultv);

		private:
			priv::ParamParserPrivate *priv;
		};
	}
}

#endif
