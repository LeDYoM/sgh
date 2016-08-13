#ifndef LIB_MANAGERS_FILESYSTEM_HPP
#define LIB_MANAGERS_FILESYSTEM_HPP

#include "basemanager.hpp"

namespace lib
{
	class File;

	namespace core
	{
		namespace managers
		{

			class FileSystem : public BaseManager<File>
			{
			public:
				using BaseClass = BaseManager<File, str>;
				using BaseManager::BaseManager;

				virtual ~FileSystem();
			};
		}
	}
}
#endif
