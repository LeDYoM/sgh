#ifndef __LIB_RESOURCEMANAGER_HPP__
#define __LIB_RESOURCEMANAGER_HPP__

#include <lib/include/types.hpp>
#include "appservice.hpp"
#include "datamap.hpp"
#include "vecsptr.hpp"

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
		VecSPtr<Resource> m_resources;
		DataMap m_resourceDescriptionList;
		std::string m_resourcesDirectory;
	};
}

#endif
