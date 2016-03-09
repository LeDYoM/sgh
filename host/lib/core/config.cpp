#include "config.hpp"
#include "log.hpp"
#include "appcontroller.hpp"
#include "filesystem.hpp"
#include "exceptionmanager.hpp"
#include "strutils.hpp"

namespace lib
{
	namespace core
	{
		Config::Config()
		{
		}

		void Config::loadFile(const std::string &fileName)
		{
			loadFile(appController()->fileSystem()->getFile(fileName));
		}

		void Config::loadFile(sptr<File> file)
		{
			if (file->exists())
			{
				auto data = file->asText();
				std::stack<std::string> currentSections;
				std::stack<ConfigSection*> current;
				current.push(&m_mainSection);

				for (const auto &line : data)
				{
					std::string temp(line);

					trim(temp);

					if (!temp.empty())
					{
						if (temp[0] == '[' && temp[temp.size() - 1] == ']')
						{
							std::string sectionName = temp.substr(1, temp.size() - 2);
							if (sectionName[0] == '/')
							{
								// End of section
								if (currentSections.size() < 1 || sectionName.substr(1) != currentSections.top())
								{
									ADD_EXCEPTION_INTERNAL("ConfigError", "ParsingError",
										"Error parsing config file " + file->fileName() + " Section " + currentSections.top() + " not closed");
									return;
								}
								else
								{
									currentSections.pop();
									current.pop();
									LOG_DEBUG_("Finished config section: " + sectionName);
								}
							}
							else
							{
								currentSections.push(sectionName);
								current.top()->sections[sectionName] = ConfigSection{};
								current.push(&(current.top()->sections[sectionName]));
								LOG_DEBUG_("Added config section: " + sectionName);
							}
						}
						else
						{
							auto pos = temp.find('=');
							if (pos == std::string::npos)
							{
								ADD_EXCEPTION_INTERNAL("ConfigError", "ParsingError",
									"Separator '=' not found. " + file->fileName() + " Section " + currentSections.top() + " not closed");
								return;
							}
							else
							{
								auto part_start = temp.substr(0, pos);
								auto part_finish = temp.substr(pos + 1);
								current.top()->data[part_start] = part_finish;
							}
						}
					}
				}
				if (currentSections.size() > 0)
				{
					// There are open sections
					std::string temp;
					while (currentSections.size() > 0)
					{
						temp += currentSections.top() + " ";
						currentSections.pop();
					}
					ADD_EXCEPTION_INTERNAL("ConfigError", "OpenSections", "The following sections are open in the config file at end of reading: " + temp);
				}
			}
		}

		const lib::core::ConfigSection & Config::section(const std::string &cname)
		{
			return m_mainSection.sections[cname];
		}

		void ConfigSection::for_each_property(std::function<void(const std::pair<std::string, std::string>&)> callback) const
		{
			std::for_each(data.begin(), data.end(), callback);
		}

	}
}
