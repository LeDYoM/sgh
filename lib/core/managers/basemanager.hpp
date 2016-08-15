#ifndef LIB_BASEMANAGER_HPP
#define LIB_BASEMANAGER_HPP


#include <lib/core/compileconfig.hpp>
#include <lib/include/types.hpp>
#include <map>
#include <vector>
#include <lib/core/obj.hpp>

namespace lib
{
	namespace core
	{
		class AppController;
		namespace managers
		{
			template <class T, class INDEXTYPE = str>
			class BaseManager : public SystemObject
			{
			public:
				using IndexType = INDEXTYPE;
				using ManagerResources = std::map<INDEXTYPE, T*>;

				using SystemObject::SystemObject;

				inline bool exists(const INDEXTYPE &index) const { return m_managedResources.find(index) != m_managedResources.end(); }
				inline T *get(const INDEXTYPE &index) const
				{
					auto iterator(m_managedResources.find(index));
					if (iterator != m_managedResources.end()) {
						return iterator->second;
					}
					return nullptr;
				}

				inline bool set(const INDEXTYPE &index, T* resource, bool overwrite=false)
				{
					if (overwrite || !exists(index)) {
						m_managedResources[index] = resource;
						return true;
					}
					return false;
				}
			protected:
				virtual ~BaseManager() { m_managedResources.clear(); }
				ManagerResources m_managedResources;
			};
		}
	}
}
#endif
