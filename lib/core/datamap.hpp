#ifndef LIB_DATA_HPP__
#define LIB_DATA_HPP__

#include <lib/include/compconfig.hpp>
#include "datavalue.hpp"
#include <map>

namespace lib
{
	class LIB_API DataMap : public std::map<str, DataValue>
	{
	public:
		using Base = std::map<str, DataValue>;

		const Base::mapped_type& operator[](const str& index) const
		{
			return find(index)->second;
		}

		using Base::operator[];
	};
	template <typename T>
	vector2d<T> fromDataMap(const DataMap &map, const str &xStr, const str& yStr)
	{
		vector2d<T> x( map[xStr].get<T>(),map[yStr].get<T>() );
		return x;
	}
}

#endif
