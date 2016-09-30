#ifndef LIB_PROPERTIES_HPP
#define LIB_PROPERTIES_HPP

#include "comp_config.hpp"
#include "serialization.hpp"

#include <algorithm>
#include <vector>

namespace vtx
{
	template <typename T>
	class VORTEX_API Property
	{
	public:
		constexpr Property() : m_value{} {}
		explicit Property(const T&iv) : m_value{ iv } {}
		constexpr Property(T&&iv) : m_value{ std::move(iv) } {}
		constexpr operator T() const { return m_value; }
		T& operator ()() { return m_value; }
		T* operator->() { return &m_value; }
		Property &operator=(const T&rh) { m_value = rh; return *this; }

		const T* operator->() const { return &m_value; }
	private:
		T m_value;
	};

	class VORTEX_API NotifablePropertyBase
	{
	public:
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
	protected:
		bool m_changedFlag{ true };
	};

	template <typename T>
	class VORTEX_API NotifableProperty : public NotifablePropertyBase
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

	private:
		T m_value;
	};

/*
	EXPIMP_TEMPLATE template class VORTEX_API std::vector<NotifablePropertyBase*>;
	using NotifablePropertyBaseVector = std::vector<NotifablePropertyBase*>;

	class VORTEX_API LinkedNotifableProperty
	{
	public:
		LinkedNotifableProperty() = default;
		LinkedNotifableProperty(std::initializer_list<NotifablePropertyBase*> properties)
		{
			for (NotifablePropertyBase* pr : properties) {
				m_properties.emplace_back(pr);
			}
		};

		bool changed() const {
			return std::any_of(m_properties.cbegin(), m_properties.cend(), [](const NotifablePropertyBase* pr) { return pr->changed(); });
		}

		void resetChanged() { 
			std::for_each(m_properties.begin(), m_properties.end(), [](NotifablePropertyBase *pr) { pr->resetChanged(); });
		}

		operator bool() const
		{
			return changed();
		}


	private:
		NotifablePropertyBaseVector m_properties;
	};
	*/
}

#endif
