#ifndef FILESYSTEM_INTERFACE_INCLUDE_HPP
#define FILESYSTEM_INTERFACE_INCLUDE_HPP

#include <moduler/include/imoduleexport.hpp>

namespace filesystem
{
	class IFileSystem : public virtual moduler::IModule
	{
	public:
		IFileSystem() {}
		virtual ~IFileSystem() {}
	};
}

DECLARE_MODULE_CREATION

#endif
