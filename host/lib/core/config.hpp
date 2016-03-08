#ifndef __LIB_CONFIG_HPP__
#define __LIB_CONFIG_HPP__

#include <lib/include/types.hpp>
#include "appservice.hpp"
#include "file.hpp"
#include <functional>

namespace lib
{
	namespace core
	{
		class ConfigSection : public TreeData<std::string, ConfigSection>
		{
		public:
			void for_each_property(std::function<void(const std::pair<std::string, std::string>&)> callback) const;
		};

		class Config : public AppService
		{
		public:
			Config();
			virtual ~Config() {}
			void loadFile(const std::string &fileName);
			void loadFile(sptr<File> file);

		private:
			ConfigSection m_mainSection;

		};
	}
}

#endif
