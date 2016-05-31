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
		Property(const T&iv) : m_value{ iv } {}
		Property(T&&iv) : m_value{ std::move(iv) } {}
		Property(const Property&) = delete;
		virtual Property &operator=(const T&nv) { m_value=nv; return *this; }
		virtual Property &operator=(T&&nv) { std::swap(m_value,nv); return *this; }
		operator const T&() const { return m_value; }
		const T *const operator ->() const { return &m_value; }
		virtual T *operator ->() { return &m_value; }

	private:
		T m_value;
	};

	template <typename T>
	class NotifableProperty : public Property<T>
	{
	public:
		using Property::Property;

		explicit NotifableProperty(const NotifableProperty &iv) = delete;
		virtual NotifableProperty &operator=(const T&nv) override { Property::operator=(nv); m_changedFlag = true; return *this; }
		virtual NotifableProperty &operator=(T&&nv) { Property::operator=(nv); m_changedFlag = true; return *this; }
		virtual T *operator ->() { m_changedFlag = true; return Property::operator ->(); }

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

#endif
