#include "file.hpp"
#include "filesystem.hpp"

namespace lib
{
	namespace core
	{
		File::File(FileSystem *const fileSystem_)
			: fileSystem{ fileSystem_ }
		{

		}

		File::~File()
		{

		}
	}
}

