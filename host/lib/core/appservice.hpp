#ifndef __LIB_APP_SERVICE_HPP__
#define __LIB_APP_SERVICE_HPP__

#include <string>

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
		core::AppController *const appController() { return m_appController; }
		virtual void Setup() {}
		virtual void Init() {}
		virtual void Close() {}
		virtual const std::string serviceName() = 0;
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
