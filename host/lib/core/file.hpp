#ifndef LIB_FILE_HPP
#define LIB_FILE_HPP

#include <lib/include/types.hpp>
#include "appservice.hpp"
#include <string>

namespace lib
{
	namespace core
	{
		class FileSystem;
		class File
		{
		public:
			File(FileSystem *const fileSystem, const std::string &fileName);
			virtual ~File();
		private:
			FileSystem *const m_fileSystem;
			std::string m_fileName;
		};
	}
}
#endif
