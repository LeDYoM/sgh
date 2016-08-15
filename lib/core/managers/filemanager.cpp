#include "filemanager.hpp"
#include <lib/core/file.hpp>
#include <lib/core/filepath.hpp>
#include <fstream>

namespace lib
{
	namespace core
	{
		namespace managers
		{
			FileManager::~FileManager()
			{
			}

			File*const FileManager::load(const BaseClass::IndexType &index)
			{
				if (!exists(index)) {
					std::ifstream file(index);
					if (file) {
						std::vector<u8> result;
						while (file) {
							char temp;
							file.read(&temp, 1);
							result.push_back(temp);
						}
						File *file(new File(result, FilePath(index)));
						set(index, file);
					}
				}
				return get(index);
			}

			File *const FileManager::load(const FilePath &path)
			{
				return load(path.c_str());
			}

		}
	}
}

