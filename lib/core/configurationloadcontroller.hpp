#ifndef __LIB_CONFIGURATIONLOADCONTROLLER_HPP__
#define __LIB_CONFIGURATIONLOADCONTROLLER_HPP__

#include <lib/include/types.hpp>
#include "strmap.hpp"
#include "filepath.hpp"

namespace lib
{
	namespace core
	{
		namespace managers
		{
			class FileManager;
			class ConfigurationManager;
		}
		class ConfigurationLoadController
		{
		public:
			ConfigurationLoadController(const ConfigurationLoadController&) = delete;
			ConfigurationLoadController& operator=(const ConfigurationLoadController&) = delete;

			ConfigurationLoadController(const FilePath &, managers::ConfigurationManager *const,
				managers::FileManager *const);
			virtual ~ConfigurationLoadController();

			bool operator()();
		private:
			managers::ConfigurationManager *const m_configurationManager;
			managers::FileManager *const m_fileManager;
			FilePath m_filePath;
		};
	}
}

#endif
