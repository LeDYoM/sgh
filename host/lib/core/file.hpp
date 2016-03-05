#ifndef LIB_FILESYSTEM_HPP
#define LIB_FILESYSTEM_HPP

#include <lib/include/types.hpp>
#include "appservice.hpp"

namespace lib
{
	namespace core
	{
		class FileSystem;
		class File
		{
		public:
			File(FileSystem *const fileSystem_);
			virtual ~File();
		private:
			FileSystem *const fileSystem;
		};
	}
}
#endif
