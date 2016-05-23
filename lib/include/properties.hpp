#ifndef LIB_PROPERTIES_HPP
#define LIB_PROPERTIES_HPP

#include "types.hpp"

namespace lib
{
	template <typename T>
	class Property
	{
	public:
		Property() : m_value{} {}
		Property(Property&&r) : m_value{ std::move(p); } {}
		explicit Property(const T&iv) :m_value{ iv } {}
		explicit Property(const T&&iv) :m_value{ std::move(iv) } {}
		explicit Property(const Property &p) : m_value{ p } {}
		Property &operator=(const T&nv) { m_value = nv; return *this; }
		Property &operator=(T&&nv) { m_value = nv; return *this; }
	private:
		T m_value;
	};
}
#endif
