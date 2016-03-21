#ifndef LIB_PROPERTIES_HPP
#define LIB_PROPERTIES_HPP

#include "types.hpp"

namespace lib
{
	template <typename T,class ACCESSOR>
	class Property
	{
	public:
		const T &get() const { return m_value; }
	private:
		Property() : m_value{} {}
		Property(Property&&r) : m_value{ std::move(p); } {}
		explicit Property(const T&iv) :m_value{ iv } {}
		explicit Property(const T&&iv) :m_value{ std::move(iv); } {}
		explicit Property(const Property &p) : m_value{ p } {}
		T m_value;
		void set(const T&nv) { m_value = nv; }
		Property &operator=(const T&nv) { m_value = nv; return *this; }
		Property &operator=(T&&nv) { m_value = nv; return *this; }

		friend ACCESSOR;
	};

	template <typename T, class ACCESSOR> using PropertySptr = Property<sptr<T>,ACCESSOR>;
}
#endif
