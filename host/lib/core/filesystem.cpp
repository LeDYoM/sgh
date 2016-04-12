#include "filesystem.hpp"
#include "file.hpp"

namespace lib
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

