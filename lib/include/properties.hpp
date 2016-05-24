#ifndef LIB_PROPERTIES_HPP
#define LIB_PROPERTIES_HPP

#include "types.hpp"
#include <functional>
#include <lib/include/color.hpp>

#ifndef CALL_MEMBER_FN
#define CALL_MEMBER_FN(object,ptrToMember)  ((object).*(ptrToMember))
#endif

namespace lib
{
	template <typename T>
	class Property
	{
	public:
		Property() : m_value{} {}
		explicit Property(const T&iv) :m_value{ iv } {}
		Property &operator=(const T&nv) { m_value = nv; return *this; }
		operator T() const { return m_value; }
	private:
		T m_value;
	};

	template <typename T>
	class PropertyWithMethods
	{
	public:
//		using Getter = std::function<const draw::Color()>;
//		using Setter = std::function<void(const draw::Color)>;
		explicit PropertyWithMethods(const T&iv) : m_value{ iv } {}
//		explicit PropertyWithMethods(const draw::Color&iv, Getter getter, Setter setter) :m_value{ iv }, m_getter{ getter }, m_setter{ setter } {}
//		PropertyWithMethods &operator=(const draw::Color&nv) { m_setter(nv); return *this; }
		operator const T&() const { return m_value; }
	private:
		T m_value;
//		Getter m_getter;
//		Setter m_setter;
	};
}

#undef CALL_MEMBER_FN

#endif
