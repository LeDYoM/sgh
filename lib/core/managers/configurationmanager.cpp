#include "configurationmanager.hpp"
#include <lib/core/strmap.hpp>

namespace lib
{
	namespace core
	{
		namespace managers
		{
			ConfigurationManager::~ConfigurationManager() {	}

			lib::StringMap ConfigurationManager::asStringMap() const
			{

			}

			void ConfigurationManager::add(const StringMap &stringMap, const bool overwrite)
			{
				stringMap.for_each([this,overwrite](std::pair<const StringMap::Index&, const StringMap::Value&> data) {
					set(data.first, &(static_cast<str>(data.second)), overwrite);
				});
			}

		}
	}
}
