#include "file.hpp"
#include "filesystem.hpp"
#include <fstream>
#include "exceptionmanager.hpp"
#include "appcontroller.hpp"

namespace lib
{
	File::File(FileSystem *const fileSystem, const std::string &fileName)
		: Object{fileSystem}, m_fileSystem{ fileSystem }, m_fileName(fileName)
	{

	}

	File::~File()
	{

	}

	bool File::exists() const
	{
		return static_cast<bool>(std::ifstream(m_fileName));
	}

	const std::vector<std::string> File::asText()
	{
		std::ifstream f(m_fileName);
		std::vector<std::string> result;
		if (f)
		{
			std::string temp;
			while (std::getline(f, temp))
			{
				result.push_back(temp);
			}
		}
		else
		{
			service<core::ExceptionManager>()->addException(EXCEPTION_INTERNAL("FileNotFound", "", "Cannot find or open file " + m_fileName));
		}
		return result;
	}

	const std::string File::fileName() const
	{
		return m_fileName;
	}
}

