#ifndef LIB_MANAGERS_FILEMANAGER_HPP
#define LIB_MANAGERS_FILEMANAGER_HPP

#include "basemanager.hpp"

namespace lib
{
	namespace core
	{
		class File;
		class FilePath;

		namespace managers
		{
			class FileManager : public BaseManager<File>
			{
			public:
				using BaseClass = BaseManager<File, str>;
				using BaseManager::BaseManager;

				virtual ~FileManager();

				File *const load(const FilePath &);
				File *const load(const BaseClass::IndexType &);
			};
		}
	}
}

#endif
