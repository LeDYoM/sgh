#ifndef LIB_DATACONVERSION_HPP
#define LIB_DATACONVERSION_HPP

#include <lib/include/types.hpp>
#include "datamap.hpp"
#include "datavalue.hpp"
#include "compileconfig.hpp"

namespace lib
{
	template <typename T>
	vector2d<T> fromDataMap(const DataMap &map, std::initializer_list<str> iList)
	{
		return std::move(vector2d<T>{ map[*(iList.begin())].get<T>(), map[*(iList.begin() + 1)].get<T>() });
	}


	inline bool canConvertfromDataMap(const DataMap &map, std::initializer_list<str> iList)
	{
		return map.containsProperties(iList);
	}
}

#endif
