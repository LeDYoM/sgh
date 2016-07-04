#ifndef LIB_PROPERTIES_HPP
#define LIB_PROPERTIES_HPP

#include "types.hpp"
#include <functional>
#include <lib/include/color.hpp>

namespace lib
{
	template <typename T>
	class Property
	{
	public:
		explicit Property() : m_value{} {}
		explicit Property(const T&iv) : m_value{ iv } {}
		Property(T&&iv) : m_value{ std::move(iv) } {}
		operator T() const { return m_value; }
		T& operator ()() { return m_value; }
		T* operator->() { return &m_value; }
		Property &operator=(const T&rh) { m_value = rh; return *this; }

		const T* operator->() const { return &m_value; }
	private:
		T m_value;
	};

	template <typename T>
	class NotifableProperty
	{
	public:
		explicit NotifableProperty() : m_value{} {}
		explicit NotifableProperty(const T&iv) : m_value{ iv } {}
		NotifableProperty(T&&iv) : m_value{ std::move(iv) } {}

		const T& operator ()() const { return m_value; }
		T& operator ()() { m_changedFlag = true; return m_value; }
		const T* operator->() const { return &m_value; }
		T* operator->() { m_changedFlag = true; return &m_value; }
		NotifableProperty &operator=(const T&rh) { m_changedFlag = true; m_value = rh; return *this; }

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
		T m_value;
		bool m_changedFlag{ true };
	};

}

#endif
