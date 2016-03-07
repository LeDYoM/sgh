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

		class ResourceManager : public AppService
		{
		public:
			ResourceManager(const std::string &resourceFile);
			virtual ~ResourceManager();
			void Init() override;
			sptr<Resource> getResource(const std::string rid);

		private:
			std::vector<sptr<Resource>> resources;
			const std::string m_resourceFile;
		};
	}
}

#endif
