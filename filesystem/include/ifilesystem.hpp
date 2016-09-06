#ifndef FILESYSTEM_INTERFACE_INCLUDE_HPP
#define FILESYSTEM_INTERFACE_INCLUDE_HPP

#include <moduler/include/imoduleexport.hpp>
#include <string>
#include <vector>

namespace filesystem
{
	class IFileSystem : public virtual moduler::IModule
	{
	public:
		IFileSystem() {}
		virtual ~IFileSystem() {}

		virtual std::vector<std::string> readFileAsStringVector(const std::string &fileName) = 0;
		virtual std::vector<char> readFile(const std::string &fileName) = 0;
	};
}

DECLARE_MODULE_CREATION

#endif
