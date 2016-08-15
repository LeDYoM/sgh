#include "configurationmanager.hpp"
#include <lib/core/strmap.hpp>

namespace lib
{
	namespace core
	{
		namespace managers
		{
			ConfigurationManager::~ConfigurationManager() {	}

			void ConfigurationManager::add(const StringMap &stringMap, const bool overwrite)
			{
				stringMap.for_each([this,overwrite](std::pair<const StringMap::Index&, const StringMap::Value&> data) {
					str *copy = new str(data.second);
					set(data.first, copy, overwrite);
				});
			}
		}
	}
}
