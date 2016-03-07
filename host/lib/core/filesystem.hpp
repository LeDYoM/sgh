#ifndef LIB_FILESYSTEM_HPP
#define LIB_FILESYSTEM_HPP

#include <lib/include/types.hpp>
#include "appservice.hpp"
#include <string>

namespace lib
{
	namespace core
	{
		class File;

		class FileSystem : public AppService
		{
		public:
			FileSystem();
			virtual ~FileSystem();

			sptr<File> getFile(const std::string &fileName);

		};
	}
}
#endif
