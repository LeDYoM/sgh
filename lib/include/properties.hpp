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
		Property(const Property&) = delete;
		virtual Property &operator=(const T&nv) { m_value=nv; return *this; }
		operator T() { return m_value; }
	private:
		T m_value;
	};

	template <typename T>
	class NotifableProperty : public Property<T>
	{
	public:
		explicit NotifableProperty(const T&iv) : Property{ iv } {}
		explicit NotifableProperty(const NotifableProperty &iv) = delete;
		virtual NotifableProperty &operator=(const T&nv) override { Property::operator=(nv); m_changedFlag = true; return *this; }
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
	private:
		bool m_changedFlag;
	};

}

#undef CALL_MEMBER_FN

#endif
