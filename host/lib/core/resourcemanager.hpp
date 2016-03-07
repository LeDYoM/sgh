#ifndef __LIB_RESOURCEMANAGER_HPP__
#define __LIB_RESOURCEMANAGER_HPP__

#include <lib/include/types.hpp>
#include "configuration.hpp"
#include "appservice.hpp"

namespace lib
{
	namespace core
	{
		class Resource;
		class ConfigSection;
		class ResourceManager : public AppService
		{
		public:
			ResourceManager();
			virtual ~ResourceManager();
			void Init() override;
			sptr<Resource> getResource(const std::string rid);
			void setResourceList(const ConfigSection &resourceList);
		private:
			void load();
			std::vector<sptr<Resource>> resources;
			bool m_loaded{ false };
		};
	}
}

#endif
