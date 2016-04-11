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

	void ServicesManager::addServiceInstance(uptr<AppService> newService)
	{
		m_services.push_back(std::move(newService));
	}

	void ServicesManager::setupAllServices()
	{
		for (auto &service : m_services)
		{
			service->PrivateSetup(m_appController);
		}
	}

	void ServicesManager::initializeServices()
	{
		for (auto &service : m_services)
		{
			service->Init();
		}
	}


}
