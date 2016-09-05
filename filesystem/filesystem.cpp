#include "include/filesystem.hpp"
#include <logger/include/logger.hpp>

namespace filesystem
{
	DECLARE_MODULE_INFORMATION_BEGIN
	DECLARE_MODULE_INFORMATION_NAME(AppRunner),
	DECLARE_MODULE_INFORMATION_VERSION(0),
	DECLARE_MODULE_INFORMATION_SUBVERSION(1),
	DECLARE_MODULE_INFORMATION_PATCH(3)
	DECLARE_MODULE_INFORMATION_END

	FileSystem::FileSystem()
	{
	}

	FileSystem::~AppRunner()
	{
	}
	moduler::ModuleInformation * const FileSystem::moduleInformation() const
	{
		return &moduleInfo;
	}

	bool FileSystem::start()
	{
		return true;
	}

	bool FileSystem::stop()
	{
		return true;
	}

	bool FileSystem::update()
	{
		return true;
	}
}

using namespace filesystem;
DEFINE_MODULE_CREATION(FileSystem);
