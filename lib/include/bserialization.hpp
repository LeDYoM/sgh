#ifndef LIB__BASIC_SERIALIZATION_HPP__
#define LIB__BASIC_SERIALIZATION_HPP__

#include "compconfig.hpp"
#include <lib/core/data.hpp>
#include "types.hpp"

namespace lib
{
	template <typename T>
	DataMap &operator<<(DataValue &old, const vector2d<T> &source)
	{
		return DataMap{ 
			{ "x", DataValue{ source.x } },
			{ "y", DataValue{ source.y } }
		};
	}
}

#endif
