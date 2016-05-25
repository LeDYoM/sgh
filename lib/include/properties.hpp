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
		explicit Property(const T&iv) : m_value{ iv } {}
		Property &operator=(const T&nv) { m_value=nv; return *this; }
		operator const T&() const { return m_value; }
	private:
		T m_value;
	};

	template <typename T>
	class NotifableProperty : public Property<T>
	{
	public:
		explicit NotifableProperty(const T&iv) : Property{ iv } {}
		NotifableProperty &operator=(const T&nv) { Property::operator=(nv); m_changedFlag = true; return *this; }
		bool changed() const { return m_changedFlag; }
		void resetChanged() { m_changedFlag = false; }
		bool readResetChanged()
		{ 
			if (m_changedFlag)
			{
				m_changedFlag = false;
				return true;
			}
			return false;
		}
		operator const T&() const { return Property::operator const T&(); }
	private:
		bool m_changedFlag;
	};

}

#undef CALL_MEMBER_FN

#endif
