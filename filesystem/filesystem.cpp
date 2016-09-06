#include "filesystem.hpp"
#include <logger/include/logger.hpp>
#include <fstream>

namespace filesystem
{
	DECLARE_MODULE_INFORMATION_BEGIN
	DECLARE_MODULE_INFORMATION_NAME(FileSystem),
	DECLARE_MODULE_INFORMATION_VERSION(0),
	DECLARE_MODULE_INFORMATION_SUBVERSION(1),
	DECLARE_MODULE_INFORMATION_PATCH(1)
	DECLARE_MODULE_INFORMATION_END

	using namespace std;

	FileSystem::FileSystem()
	{
	}

	FileSystem::~FileSystem()
	{
	}
	moduler::ModuleInformation * const FileSystem::moduleInformation() const
	{
		return &moduleInfo;
	}

	bool FileSystem::start()
	{
		return true;
	}

	bool FileSystem::stop()
	{
		return true;
	}

	vector<string> FileSystem::readFileAsStringVector(const string & fileName)
	{
		auto data{ readFile(fileName) };
		vector<string> result;
		string temp;

		for (const auto ch : data) {
			if (ch != '\n' && ch != 0x13) {
				temp.push_back(ch);
			}
			else {
				if (!temp.empty()) {
					result.push_back(temp);
					temp.clear();
				}
			}
		}

		return move(result);
	}

	vector<char> FileSystem::readFile(const string &fileName)
	{
		std::ifstream file(fileName);
		if (file) {
			std::vector<char> result;
			while (file) {
				char temp;
				file.read(&temp, 1);
				result.emplace_back(temp);
			}
			return result;
		}
		return std::vector<char>{};
	}
}

using namespace filesystem;
DEFINE_MODULE_CREATION(FileSystem);
