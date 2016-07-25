#ifndef __LIB_APPCONTROLLER_HPP__
#define __LIB_APPCONTROLLER_HPP__

#include <lib/include/types.hpp>
#include <lib/include/iapp.hpp>
#include <lib/include/iappcontext.hpp>
#include <lib/core/vecsptr.hpp>
#include <vector>
#include <string>

namespace lib
{
	class AppService;
	class ServicesManager;

	class IAppContext
	{
	protected:
		virtual ~IAppContext() {}
	};

	namespace core
	{
		class Driver;
	
		class AppController : public IAppContext
		{
		public:
			enum class AppState
			{
				NotInitialized,
				ReadyToStart,
				Executing,
				ReadyToTerminate,
				Terminated
			};
			AppController(uptr<IApp> iapp,sptr<Driver> driverInstance);
			virtual ~AppController();
			
			bool update();
			sptr<Driver> const &driver() const { return m_driver; }

			uptr<ServicesManager> const &servicesManager() const { return m_servicesManager; }
			sptr<Window> window() const { return m_window; }

			const std::string appId() const;

		protected:
			bool loopStep();

		private:
			uptr<ServicesManager> m_servicesManager;
			AppState m_state;
			uptr<IApp> m_iapp{ nullptr };
			sptr<Driver> m_driver{ nullptr };
			std::vector<uptr<AppService>> m_services;
			sptr<Window> m_window;
		};

		AppController *toController(PIAppContext context);
	}
}

#endif
