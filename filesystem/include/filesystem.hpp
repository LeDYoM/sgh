#ifndef FILESYSTEM_INCLUDE_HPP
#define FILESYSTEM_INCLUDE_HPP

#include "filesystem.hpp"

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

		virtual bool update() override;

	};
}

#endif
