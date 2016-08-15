#ifndef __LIB_CORE_TYPES_HPP__
#define __LIB_CORE_TYPES_HPP__

#include <lib/include/types.hpp>
#include <map>
#include <algorithm>
#include "strmap.hpp"
#include "strutils.hpp"

namespace lib
{
	namespace core
	{
		using DataTypeInternal = std::map<StringMap::Index, StringMap::Value>;
		using Node = std::pair<StringMap::Index, StringMap::Value>;

		struct StringMapPrivate
		{
			DataTypeInternal m_data;
			StringMapPrivate() = default;
			StringMapPrivate(const StringMapPrivate &) = default;
			StringMapPrivate &operator=(const StringMapPrivate&) = default;
			StringMapPrivate(StringMapPrivate &&) = default;
			StringMapPrivate &operator=(StringMapPrivate&&) = default;
		};

		StringMap::StringMap()
			: m_private(new StringMapPrivate) {	}

		StringMap::StringMap(const std::vector<str> &dataVector, const str &separator)
		{
			for (const auto &data : dataVector) {
				str left(data);
				str right(data);
				leftFrom(left, separator);
				trim(left);
				rightFrom(right, separator);
				trim(right);
				if (!left.empty()) {
					m_private->m_data[left] = right;
				}
			}
		}

		StringMap::~StringMap()
		{
			if (m_private)
				delete m_private;
		}

		StringMap::StringMap(const StringMap &rh)
			: m_private(rh.m_private) {	}

		StringMap & StringMap::operator=(const StringMap &rh)
		{
			m_private->m_data = rh.m_private->m_data;
			return *this;
		}

		StringMap::StringMap(StringMap &&rh)
			: m_private(std::move(rh.m_private))
		{
			rh.m_private = nullptr;
		}

		StringMap & StringMap::operator=(StringMap &&rh)
		{
			std::swap(m_private, rh.m_private);
			return *this;
		}

		bool StringMap::exists(const Index &index) const
		{
			return m_private->m_data.find(index) != m_private->m_data.end();
		}

		bool StringMap::add(const Index &index, const Value value)
		{
			if (!exists(index)) {
				m_private->m_data[index] = value;
				return true;
			}
			return false;
		}

		bool StringMap::update(const Index &index, const Value value)
		{
			if (exists(index)) {
				m_private->m_data[index] = value;
				return true;
			}
			return false;
		}

		StringMap StringMap::subMap(const Index &index) const
		{
			StringMap result;
			for (Node node : m_private->m_data) {
				if (!(node.first.find_first_of(index))) {
					result.add(node.first, node.second);
				}
			}
			return std::move(result);
		}

		void StringMap::for_each(std::function<void(std::pair<const Index &, const Value&>)> precdicate) const
		{
			std::for_each(m_private->m_data.cbegin(), m_private->m_data.cend(), precdicate);
		}
	}
}

#endif
