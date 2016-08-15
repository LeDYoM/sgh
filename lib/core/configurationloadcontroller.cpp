#include "configurationloadcontroller.hpp"
#include "managers/filemanager.hpp"
#include "managers/configurationmanager.hpp"
#include "file.hpp"
#include "log.hpp"

namespace lib
{
	namespace core
	{
		ConfigurationLoadController::ConfigurationLoadController(const FilePath &filePath,
			managers::ConfigurationManager *const configurationManager, managers::FileManager *const fileManager)
			: m_filePath{ filePath }, m_configurationManager{ configurationManager }, m_fileManager{ fileManager } {}

		ConfigurationLoadController::~ConfigurationLoadController()
		{
		}

		bool ConfigurationLoadController::operator()()
		{
			StringMap stringMap{ m_fileManager->load(m_filePath)->asText(), "=" };

			// For each entry in the data
			m_configurationManager->add(stringMap,true);
			return true;
		}
	}
}
