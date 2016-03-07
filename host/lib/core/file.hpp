#ifndef LIB_FILE_HPP
#define LIB_FILE_HPP

#include <lib/include/types.hpp>
#include "appservice.hpp"
#include <string>
#include <vector>

namespace lib
{
	namespace core
	{
		class FileSystem;
		class File
		{
		public:
			File(FileSystem *const fileSystem, const std::string &fileName);
			File &operator=(const File&rh) = delete;
			virtual ~File();

			bool exists() const;
			const std::vector<std::string> asText();
			const std::string fileName() const;
		private:
			FileSystem *const m_fileSystem;
			std::string m_fileName;
		};
	}
}
#endif
