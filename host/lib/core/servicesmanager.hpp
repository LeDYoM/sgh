#ifndef LIB_SERVICESMANAGER_HPP
#define LIB_SERVICESMANAGER_HPP

#include <vector>
#include <lib/include/types.hpp>

namespace lib
{
	class AppService;
	namespace core
	{
		class AppController;
	}
	class ServicesManager
	{
	public:
		ServicesManager(core::AppController *appController);
		virtual ~ServicesManager();

		void addServiceInstance(uptr<AppService> newService);
		void setupAllServices();
		void initializeServices();
	private:
		std::vector<sptr<AppService>> m_services;
		core::AppController *m_appController;
	};
}
#endif
