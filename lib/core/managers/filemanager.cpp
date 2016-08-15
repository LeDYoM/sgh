#include "filemanager.hpp"
#include <lib/core/file.hpp>
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

			void FileManager::load(const BaseClass::IndexType &index)
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
			}
		}
	}
}

