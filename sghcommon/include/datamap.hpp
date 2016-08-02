#ifndef LIB_DATA_HPP__
#define LIB_DATA_HPP__

#include "datavalue.hpp"
#include <initializer_list>
#include <map>

namespace lib
{
	class DataMap : public std::map<str, DataValue>
	{
	private:
		DataValue empty{};

	public:

		using Base = std::map<str, DataValue>;

		inline const Base::mapped_type& operator[](const str& index) const
		{
			auto result(find(index));
			return result == end()?empty:result->second;
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
}

#endif
