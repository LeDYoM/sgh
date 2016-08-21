#include "include/strmap.hpp"
#include <algorithm>
#include <map>

namespace ext
{
	using DataTypeInternal = std::map<StrMap::Index, StrMap::Value>;
	using Node = std::pair<StrMap::Index, StrMap::Value>;

	struct StringMapPrivate
	{
		DataTypeInternal m_data;
		StringMapPrivate() = default;
		StringMapPrivate(const StringMapPrivate &) = default;
		StringMapPrivate &operator=(const StringMapPrivate&) = default;
	};

	StrMap::StrMap()
		: m_private(new StringMapPrivate) {	}

	StrMap::StrMap(const std::vector<str> &dataVector, const str &separator)
	{
		for (const auto &data : dataVector) {
			str left(data);
			str right(data);
			left.leftFrom(separator).trim();
			right.rightFrom(separator).trim();

			if (!left.empty()) {
				m_private->m_data[left] = right;
			}
		}
	}

	StrMap::~StrMap()
	{
		if (m_private)
			delete m_private;
	}

	StrMap::StrMap(const StrMap &rh)
		: m_private(rh.m_private) {	}

	StrMap & StrMap::operator=(const StrMap &rh)
	{
		m_private->m_data = rh.m_private->m_data;
		return *this;
	}

	StrMap::StrMap(StrMap &&rh)
		: m_private(std::move(rh.m_private))
	{
		rh.m_private = nullptr;
	}

	StrMap & StrMap::operator=(StrMap &&rh)
	{
		std::swap(m_private, rh.m_private);
		return *this;
	}

	bool StrMap::exists(const Index &index) const
	{
		return m_private->m_data.find(index) != m_private->m_data.end();
	}

	bool StrMap::add(const Index &index, const Value value)
	{
		if (!exists(index)) {
			m_private->m_data[index] = value;
			return true;
		}
		return false;
	}

	bool StrMap::update(const Index &index, const Value value)
	{
		if (exists(index)) {
			m_private->m_data[index] = value;
			return true;
		}
		return false;
	}

	StrMap StrMap::subMap(const Index &index) const
	{
		StrMap result;
		for (Node node : m_private->m_data) {
			if (!(node.first.find_first_of(index))) {
				result.add(node.first, node.second);
			}
		}
		return std::move(result);
	}

	void StrMap::for_each(std::function<void(std::pair<const Index &, const Value&>)> precdicate) const
	{
		std::for_each(m_private->m_data.cbegin(), m_private->m_data.cend(), precdicate);
	}
}