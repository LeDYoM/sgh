#include "servicesmanager.hpp"
#include "appservice.hpp"
#include "datamap.hpp"
#include "input.hpp"
#include "exceptionmanager.hpp"
#include "utilprovider.hpp"
#include <lib/draw/scenemanager.hpp>
#include <lib/draw/rendermanager.hpp>
#include "managers/fontmanager.hpp"
#include "managers/texturemanager.hpp"
#include "managers/filemanager.hpp"
#include "managers/configurationmanager.hpp"

namespace lib
{
	namespace core
	{
		ServicesManager::ServicesManager(core::AppController *appController)
			: m_appController{ appController }
		{
		}

		ServicesManager::~ServicesManager()
		{
		}

		void ServicesManager::createServices()
		{
			addService(sptr<ExceptionManager>{new ExceptionManager{}});
			addService(sptr<UtilProvider>{new UtilProvider{}});
			addService(sptr<draw::SceneManager>{ new draw::SceneManager{} });
			addService(sptr<draw::RenderManager>{ new draw::RenderManager{} });
			addService(sptr<Input>{new Input{}});
		}

		void ServicesManager::for_each_service(std::function<void(std::type_index, sptr<AppService>)> callback)
		{
			for (std::pair<std::type_index, sptr<AppService>> serviceNode : m_services) {
				callback(serviceNode.first, serviceNode.second);
			}
		}

		void ServicesManager::addServiceInstance(const std::type_index &typeName, sptr<AppService> newService)
		{
			m_services[typeName] = std::move(newService);
			if (typeName == std::type_index(typeid(Input)))
				m_input = std::dynamic_pointer_cast<Input>(m_services[typeName]);
			else if (typeName == std::type_index(typeid(draw::RenderManager)))
				m_renderManager = std::dynamic_pointer_cast<draw::RenderManager>(m_services[typeName]);
			else if (typeName == std::type_index(typeid(managers::FontManager)))
				m_fontManager = std::dynamic_pointer_cast<managers::FontManager>(m_services[typeName]);
			else if (typeName == std::type_index(typeid(managers::TextureManager)))
				m_textureManager = std::dynamic_pointer_cast<managers::TextureManager>(m_services[typeName]);
			else if (typeName == std::type_index(typeid(managers::FileManager)))
				m_fileManager = std::dynamic_pointer_cast<managers::FileManager>(m_services[typeName]);
			else if (typeName == std::type_index(typeid(managers::ConfigurationManager)))
				m_configurationManager = std::dynamic_pointer_cast<managers::ConfigurationManager>(m_services[typeName]);
		}

		void ServicesManager::setupAllServices()
		{
			for_each_service([this](std::type_index, sptr<AppService> _service)
			{
				_service->PrivateSetup(m_appController);
			});
		}

		void ServicesManager::initializeServices()
		{
			for_each_service([this](std::type_index, sptr<AppService> _service)
			{
				_service->Init();
			});
		}

		void ServicesManager::stopServices()
		{
			for_each_service([this](std::type_index, sptr<AppService> _service)
			{
				_service->Stop();
			});

			m_services.clear();
		}

		void ServicesManager::processSystemEvent(sptr<DataMap> data)
		{
			for_each_service([this](std::type_index, sptr<AppService> _service)
			{
				_service->Init();
			});
		}

		sptr<AppService> ServicesManager::service(const std::type_index &serviceType) const
		{
			return m_services.at(serviceType);
		}
	}
}
