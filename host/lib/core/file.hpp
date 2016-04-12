#ifndef LIB_FILE_HPP
#define LIB_FILE_HPP

#include <lib/include/types.hpp>
#include "obj.hpp"
#include "classutils.hpp"
#include <string>
#include <vector>

namespace lib
{
	namespace core
	{
		class FileSystem;
		class File : public Object
		{
			NO_COPY(File);
		public:
			virtual ~File();
			bool exists() const;
			const std::vector<std::string> asText();
			const std::string fileName() const;

		private:
			File(FileSystem *const fileSystem, const std::string &fileName);

		private:
			friend class FileSystem;
			FileSystem *const m_fileSystem;
			std::string m_fileName;
		};
	}
}
#endif
