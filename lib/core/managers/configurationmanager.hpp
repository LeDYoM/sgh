#ifndef __LIB_CONFIGURATIONMANAGER_HPP__
#define __LIB_CONFIGURATIONMANAGER_HPP__

#include <lib/include/types.hpp>
#include "basemanager.hpp"

namespace lib
{
	namespace core
	{
		class StringMap;

		namespace managers
		{
			class ConfigurationManager : public BaseManager<str>
			{
			public:
				using BaseClass = BaseManager<str, str>;
				using BaseManager::BaseManager;

				~ConfigurationManager();

				StringMap asStringMap() const;
				void add(const StringMap &, const bool);
			};
		}
	}
}

#endif
