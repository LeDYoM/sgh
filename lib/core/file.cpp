#include "file.hpp"

namespace lib
{
	namespace core
	{
		File::File(const std::vector<u8> &data, const FilePath &path)
			: m_data( data ), m_filePath{ path } {}

		File::~File() {	}

		const std::vector<str> File::asText()
		{
			std::vector<str> result;
			str temp;

			for (const auto ch : m_data) {
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

			return std::move(result);
		}
	}
}

