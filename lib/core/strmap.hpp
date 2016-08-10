#ifndef __LIB_CORE_TYPES_HPP__
#define __LIB_CORE_TYPES_HPP__

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
			using DataTypeInternal = std::map<Index, Value>;
			using Node = std::pair<Index,Value>;

			StringMap() {}
			virtual ~StringMap() {}

			inline bool exists(Index index) const { return m_data.find(index) != m_data.end(); }
			inline bool add(Index index, const Value value)
			{
				if (!exists(index)) {
					m_data[index] = value;
					return true;
				}
				return false;
			}
			inline bool update(Index index, const Value value)
			{
				if (exists(index)) {
					m_data[index] = value;
					return true;
				}
				return false;
			}
		private:
			DataTypeInternal m_data;
		};
	}
}


#endif
