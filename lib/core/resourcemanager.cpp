#include "resourcemanager.hpp"
#include "log.hpp"
#include "resource.hpp"
#include "exceptionmanager.hpp"
#include "appcontroller.hpp"
#include "filesystem.hpp"
#include "file.hpp"
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
		auto file(service<FileSystem>()->getFile("resources.cfg"));
		std::vector<str> data{ file->asText() };
		u32 count{ 0 };
		m_resourceDescriptionList = std::move(DataValue::fromStringVector(data, count));
		load("*");
	}

	ResourceManager::~ResourceManager()
	{
		m_resources.clear();
	}

	void ResourceManager::load(const std::string &section)
	{
		m_resourcesDirectory = m_resourceDescriptionList["resources_directory"].getString();
		for (const auto tuple : m_resourceDescriptionList)
		{
			if (tuple.first != "resources_directory" && (starts_with(tuple.first, section) || section=="*"))
			{
				std::string resourceTypeStr(tuple.first);
				std::string id(tuple.first);
				leftFrom(id, "@");
				rightFrom(resourceTypeStr, "@");

				Resource::ResourceType resourceType{ Resource::ResourceType::Empty };
				resourceType = (resourceTypeStr[0] == 'f' || resourceTypeStr[0] == 'F')
					? Resource::ResourceType::Font :
					Resource::ResourceType::Texture;
				m_resources.push_back(sptr<Resource>(new Resource(resourceType, m_resourcesDirectory + tuple.second.getString(), id)));
				LOG_DEBUG("Resource with id " + tuple.second.getString() + " added");
			}
		}
	}

	sptr<Resource> ResourceManager::getResource(const std::string rid)
	{
		for (auto i = 0u; i < m_resources.size(); ++i)
		{
			if (m_resources[i]->id() == rid)
			{
				return m_resources[i];
			}
		}
		service<core::ExceptionManager>()->addException(EXCEPTION_INTERNAL("ResourceNotFound", "", "Cannot find resource " + rid));
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
