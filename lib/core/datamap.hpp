#ifndef LIB_DATA_HPP__
#define LIB_DATA_HPP__

#include <lib/include/compconfig.hpp>
#include "datavalue.hpp"
#include <initializer_list>
#include <map>

namespace lib
{
	class LIB_API DataMap : public std::map<str, DataValue>
	{
	public:
		using Base = std::map<str, DataValue>;

		inline const Base::mapped_type& operator[](const str& index) const
		{
			return find(index)->second;
		}

		using Base::operator[];

		inline bool containsProperties(std::initializer_list<str> iList) const
		{
			for (const str &element : iList)
			{
				if (find(element) == end())
				{
					return false;
				}
			}
			return true;
		}
	};

	template <typename T>
	vector2d<T> fromDataMap(const DataMap &map, std::initializer_list<str> iList)
	{
		return vector2d<T>{ map[*(iList.begin())].get<T>(), map[iList[1]].get<T>() };
	}

//	template <typename T>
	inline bool canConvertfromDataMap(const DataMap &map, std::initializer_list<str> iList)
	{
		return map.containsProperties(iList);
	}

}

#endif
