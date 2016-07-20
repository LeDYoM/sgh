#ifndef LIB_FILE_HPP
#define LIB_FILE_HPP

#include <lib/include/types.hpp>
#include "obj.hpp"
#include <string>
#include <vector>

namespace lib
{
	class FileSystem;
	class File : public Object
	{
	public:
		File() = delete;
		File(const File&) = delete;
		File &operator=(const File&) = delete;

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

#endif
