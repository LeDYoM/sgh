#ifndef __LIB_CORE_STRMAP_HPP__
#define __LIB_CORE_STRMAP_HPP__

#include <lib/include/types.hpp>
#include <map>

namespace lib
{
	namespace core
	{
		class StringMap
		{
		public:
			using Index = const str;
			using Value = str;

			StringMap();
			virtual ~StringMap();

			bool exists(Index index) const;
			bool add(Index index, const Value value);
			bool update(Index index, const Value value);
		private:
			struct StringMapPrivate *m_private;
		};
	}
}


#endif
