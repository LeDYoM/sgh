#include "resourceloadcontroller.hpp"
#include "filepath.hpp"
#include "managers/filemanager.hpp"
#include "managers/texturemanager.hpp"
#include "managers/fontmanager.hpp"
#include "log.hpp"

namespace lib
{
	namespace core
	{
		ResourceLoadController::ResourceLoadController(const StringMap &stringMap, const str &section,
			managers::FileManager *const fileManager, managers::FontManager *const fontManager, 
			managers::TextureManager *const textureManager)
			: m_stringMap{ stringMap }, m_section{ section },
			m_fileManager {fileManager},m_fontManager{ fontManager }, m_textureManager{ textureManager } {}

		ResourceLoadController::~ResourceLoadController()
		{
		}

		bool ResourceLoadController::operator()()
		{
			StringMap subMap{ m_stringMap.subMap(m_section) };

			// For each entry in the data
			subMap.for_each([](std::pair <const str&, const str&> data) {
				const FilePath filePath(data.second);
				const str extension(filePath.fileNameExtension());

				if (!filePath.empty() && !extension.empty()) {

				}

			});

		}
	}
}
