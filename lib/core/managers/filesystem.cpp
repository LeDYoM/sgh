#include "filesystem.hpp"
#include <lib/core/filesystem.hpp>

namespace lib
{
	namespace core
	{
		namespace managers
		{
			FileSystem::~FileSystem()
			{

			}

			sptr<File> FileSystem::load(const BaseClass::IndexType &fileName)
			{
				return sptr<File>();
			}

		}
	}
}

