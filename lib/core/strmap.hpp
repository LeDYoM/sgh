#ifndef __LIB_CORE_STRMAP_HPP__
#define __LIB_CORE_STRMAP_HPP__

#include <lib/include/types.hpp>
#include <functional>

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
			StringMap(const std::vector<str> &dataVector, const str &separator);

			bool exists(const Index &index) const;
			bool add(const Index &index, const Value value);
			bool update(const Index &index, const Value value);

			StringMap subMap(const Index &) const;

			void for_each(std::function<void(std::pair<const Index &, const Value&>)> precdicate) const;
		private:
			struct StringMapPrivate *m_private;
		};
	}
}


#endif
