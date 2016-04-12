#ifndef __LIB_APP_SERVICE_HPP__
#define __LIB_APP_SERVICE_HPP__

#include <string>
#include "servicesmanager.hpp"

namespace lib
{
	namespace core
	{
		class AppController;
	}

	class AppService
	{
	public:
		AppService &operator=(const AppService &rh) = delete;
		core::AppController *const appController() const { return m_appController; }
		virtual void Setup() {}
		virtual void Init() {}
		virtual void Stop() {}

		template <class T> sptr<T> service() const
		{
			return appController()->servicesManager()->service<T>();
		}
	private:
		friend class core::AppController;
		friend class ServicesManager;
		core::AppController *m_appController{ nullptr };

		void PrivateSetup(core::AppController *const appController_)
		{
			m_appController = appController_;
			Setup();
		}
	};
}
#endif
