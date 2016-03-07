#include "filesystem.hpp"
#include "file.hpp"

namespace lib
{
	namespace core
	{
		FileSystem::FileSystem()
		{
		}

		FileSystem::~FileSystem()
		{

		}

		sptr<File> FileSystem::getFile(const std::string &fileName)
		{
			return sptr<File>{new File(this, fileName)};
		}

	}
}

