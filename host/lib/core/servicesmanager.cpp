#include "servicesmanager.hpp"
#include "appservice.hpp"

namespace lib
{
	ServicesManager::ServicesManager(core::AppController *appController)
		: m_appController{ appController }
	{

	}

	ServicesManager::~ServicesManager()
	{

	}

	void ServicesManager::addServiceInstance(const std::type_index &typeName, sptr<AppService> newService)
	{
		m_services[typeName] = std::move(newService);
	}

	void ServicesManager::setupAllServices()
	{
		for (auto &service : m_services)
		{
			service.second->PrivateSetup(m_appController);
		}
	}

	void ServicesManager::initializeServices()
	{
		for (auto &service : m_services)
		{
			service.second->Init();
		}
	}


	void ServicesManager::stopServices()
	{
		for (auto &service : m_services)
		{
			service.second->Stop();
		}
		m_services.clear();
	}

	sptr<AppService> ServicesManager::service(const std::type_index &serviceType) const
	{
		return m_services.at(serviceType);
	}

}
