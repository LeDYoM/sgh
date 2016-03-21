#ifndef LIB_IPARENTABLE_HPP
#define LIB_IPARENTABLE_HPP

#include <lib/core/log.hpp>

namespace lib
{
	namespace draw
	{
		template <class T>
		class IParentable
		{
		protected:
			T *const parent() const { return m_parent; }
		private:
			T *m_parent{ nullptr };
			void setParent(T *const parent_)
			{
				__ASSERT(!m_parent, "Node already has a parent");
				m_parent = parent_;
			}

			friend T;
		};
	}
}
#endif
