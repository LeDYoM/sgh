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
			using Index = str;
			using Value = str;

			StringMap();
			~StringMap();
			StringMap(const StringMap &);
			StringMap &operator=(const StringMap &);
			StringMap(StringMap &&);
			StringMap &operator=(StringMap &&);


			bool exists(const Index &index) const;
			bool add(const Index &index, const Value value);
			bool update(const Index &index, const Value value);

			StringMap subMap(const Index &) const;
		private:
			struct StringMapPrivate *m_private;
		};
	}
}


#endif
