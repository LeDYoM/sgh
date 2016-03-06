#include "file.hpp"
#include "filesystem.hpp"

namespace lib
{
	namespace core
	{
		File::File(FileSystem *const fileSystem, const std::string &fileName)
			: m_fileSystem{ fileSystem }, m_fileName{ fileName }
		{

		}

		File::~File()
		{

		}
	}
}

