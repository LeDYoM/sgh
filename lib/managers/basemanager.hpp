#ifndef LIB_BASEMANAGER_HPP
#define LIB_BASEMANAGER_HPP


#include <lib/core/compileconfig.hpp>
#include <lib/include/types.hpp>
#include <map>
#include <vector>

namespace lib
{
	namespace manager
	{

		template <class T>
		class BaseManager
		{
		public:
			EXPIMP_TEMPLATE template class LIB_API std::map<str, sptr<T>>;
			using ManagerResources = std::map<str, sptr<T>>;

		};
	}
}
#endif
