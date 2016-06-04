#include "servicesmanager.hpp"
#include "appservice.hpp"
#include "data.hpp"
#include "input.hpp"
#include <lib/draw/rendermanager.hpp>

namespace lib
{
	ServicesManager::ServicesManager(core::AppController *appController)
		: m_appController{ appController }
	{
	}

	ServicesManager::~ServicesManager()
	{
	}

	void ServicesManager::for_each_service(std::function<void(std::type_index, sptr<AppService>)> callback)
	{
		for (std::pair<std::type_index,sptr<AppService>> serviceNode : m_services) {
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
