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
		private:
			T *m_parent{ nullptr };
			void setParent(T *const parent)
			{
				__ASSERT(!m_parent, "Node already has a parent");
				m_parent = parent;
			}

			friend T;
		};
	}
}
#endif
