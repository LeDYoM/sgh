#ifndef __LIB_RESOURCEMANAGER_HPP__
#define __LIB_RESOURCEMANAGER_HPP__

#include <lib/include/types.hpp>
#include "appservice.hpp"
#include <vector>
#include <map>

namespace lib
{
	class Resource;
	class ResourceManager : public AppService
	{
	public:
		ResourceManager();
		virtual ~ResourceManager();
		void Init() override;
		sptr<Resource> getResource(const std::string rid);
		void load(const std::string &section);
		static const str staticTypeName() { return "ResourceManager"; }

	private:
		std::vector<sptr<Resource>> resources;
		std::map<std::string, std::string> m_resourceList;
		std::string resourcesDirectory;
	};
}

#endif
