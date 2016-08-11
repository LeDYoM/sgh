#ifndef __LIB_CORE_TYPES_HPP__
#define __LIB_CORE_TYPES_HPP__

#include <lib/include/types.hpp>
#include <map>
#include "strmap.hpp"

namespace lib
{
	namespace core
	{
		using DataTypeInternal = std::map<StringMap::Index, StringMap::Value>;
		using Node = std::pair<StringMap::Index, StringMap::Value>;

		struct StringMapPrivate
		{
			DataTypeInternal m_data;

		};

		StringMap::StringMap()
			: m_private(new StringMapPrivate)
		{

		}

		StringMap::~StringMap()
		{
			delete m_private;
		}

		bool StringMap::exists(Index index) const
		{
			return m_private->m_data.find(index) != m_private->m_data.end();
		}

		bool StringMap::add(Index index, const Value value)
		{
			if (!exists(index)) {
				m_private->m_data[index] = value;
				return true;
			}
			return false;
		}

		bool StringMap::update(Index index, const Value value)
		{
			if (exists(index)) {
				m_private->m_data[index] = value;
				return true;
			}
			return false;
		}


	}
}


#endif
