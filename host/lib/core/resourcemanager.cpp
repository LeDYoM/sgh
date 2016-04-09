#include "resourcemanager.hpp"
#include "log.hpp"
#include "resource.hpp"
#include "exceptionmanager.hpp"
#include "appcontroller.hpp"
#include "configuration.hpp"
#include "strutils.hpp"
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Texture.hpp>

namespace lib
{
	ResourceManager::ResourceManager()
	{
	}

	void ResourceManager::Init()
	{
		AppService::Init();
	}

	ResourceManager::~ResourceManager()
	{
		resources.clear();
	}

	void ResourceManager::load(const std::string &section)
	{
		section;
		/*
		auto resourcesList = appController()->configuration()->section("Resources");
		resourcesDirectory = resourcesList.data["resources_directory"];
		for (const auto tuple : resourcesList.data)
		{
			if (starts_with(tuple.first, section) || section=="*")
			{
				std::string resourceTypeStr(tuple.first);
				std::string id(tuple.first);
				leftFrom(id, "@");
				rightFrom(resourceTypeStr, "@");

				Resource::ResourceType resourceType{ Resource::ResourceType::Empty };
				resourceType = (resourceTypeStr[0] == 'f' || resourceTypeStr[0] == 'F')
					? Resource::ResourceType::Font :
					Resource::ResourceType::Texture;
				resources.push_back(sptr<Resource>(new Resource(resourceType, resourcesDirectory + tuple.second, id)));
				LOG_DEBUG_("Resource with id " + tuple.second + " added");
			}
		}
		*/
	}

	sptr<Resource> ResourceManager::getResource(const std::string rid)
	{
		for (auto i = 0u; i < resources.size(); ++i)
		{
			if (resources[i]->name() == rid)
			{
				return resources[i];
			}
		}
		appController()->exceptionManager()->addException(EXCEPTION_INTERNAL("ResourceNotFound", "", "Cannot find resource " + rid));
		return sptr<Resource>();
//			throw ResourceNotFoundException(rid);
	}

	/*
	void ResourceManager::setResourceList(const ConfigSection &resourceList)
	{
		const std::string resourcesDirectoryKey = "resources_directory";

		resourceList.for_each_property([this,&resourcesDirectoryKey](const std::pair<std::string, std::string>&data)
		{
			if (data.first == resourcesDirectoryKey)
			{
				resourcesDirectory = data.second;
			}
			else
			{
				m_resourceList[data.first] = data.second;
			}
		});
	}
	*/
}
