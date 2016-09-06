#ifndef FILESYSTEM_INCLUDE_HPP
#define FILESYSTEM_INCLUDE_HPP

#include "ifilesystem.hpp"

namespace filesystem
{
	class FileSystem : public virtual IFileSystem
	{
	public:
		FileSystem();
		~FileSystem();

		virtual moduler::ModuleInformation *const moduleInformation() const override;

		virtual bool start() override;
		virtual bool stop() override;

		virtual std::vector<std::string> readFileAsStringVector(const std::string &fileName) override;
		virtual std::vector<char> readFile(const std::string &fileName) override;
	};
}

#endif
