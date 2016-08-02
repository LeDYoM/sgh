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
			bool paramEntered(const str&) const;
			s32 paramAsInt(const str&, int defaultv);
			bool paramAsBool(const str&, bool defaultv);
			const str& paramAsString(const str&, const str& defaultv);

		private:
			priv::ParamParserPrivate *priv;
		};
	}
}

#endif
