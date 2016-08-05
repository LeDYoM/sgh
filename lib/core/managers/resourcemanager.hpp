#ifndef LIB_MANAGERS_RESOURCEMANAGER_HPP
#define LIB_MANAGERS_RESOURCEMANAGER_HPP

#include "basemanager.hpp"

namespace lib
{
	namespace core
	{
		namespace managers
		{
			template <class T, class INDEXTYPE = str>
			class ResourceManager : BaseManager<T,INDEXTYPE>
			{
			public:
				using BaseManager<T, INDEXTYPE>::BaseManager;
				virtual ~ResourceManager() { }

				virtual void load(const StringMap &strMAp)
			};
		}
	}
}
#endif
