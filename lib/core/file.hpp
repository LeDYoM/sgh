#ifndef LIB_FILE_HPP
#define LIB_FILE_HPP

#include <lib/include/types.hpp>
#include "filepath.hpp"
#include <vector>

namespace lib
{
	namespace core
	{
		namespace managers
		{
			class FileManager;
		}
		class File
		{
		private:
			File() = delete;
			File(const File&) = delete;
			File &operator=(const File&) = delete;
			File(const std::vector<u8> &, const FilePath &);
			virtual ~File();
		public:
			const std::vector<str> asText();

		private:
			std::vector<u8> m_data;
			FilePath m_filePath;
			friend class managers::FileManager;
		};
	}
}

#endif
