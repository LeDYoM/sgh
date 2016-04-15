#ifndef LIB_SERVICESMANAGER_HPP
#define LIB_SERVICESMANAGER_HPP

#include <vector>
#include <lib/include/types.hpp>
#include "data.hpp"
#include <functional>
#include <typeindex>

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

		template <class T> void addService(sptr<T> newService)
		{
			addServiceInstance(std::type_index(typeid(T)), std::move(newService));
		}

		void setupAllServices();
		void initializeServices();
		void stopServices();
		void processSystemEvent(sptr<DataMap> data);

		template <class T> sptr<T> service() const
		{
			return std::dynamic_pointer_cast<T>(service(std::type_index(typeid(T))));
		}

	private:
		void for_each_service(std::function<void(std::type_index, sptr<AppService>)> callback);
		void addServiceInstance(const std::type_index &typeName, sptr<AppService> newService);
		sptr<AppService> service(const std::type_index &serviceType) const;

		std::map<std::type_index,sptr<AppService>> m_services;
		core::AppController *m_appController;
	};
}
#endif
