#ifndef __LIB_APPCONTROLLER_HPP__
#define __LIB_APPCONTROLLER_HPP__

#include <lib/include/types.hpp>
#include <lib/include/iapp.hpp>
#include <lib/core/vecsptr.hpp>
#include <vector>
#include <string>

namespace lib
{
	namespace draw
	{
		class SceneManager;
		class Scene;
	}
	class UtilProvider;
	class Configuration;
	class ResourceManager;
	class AppService;
	class ServicesManager;

	namespace core
	{
		class Window;
		class EventManager;
		class ExceptionManager;
		class FileSystem;
		class Driver;
	
		class AppController
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

			const std::string appId() const;

		protected:
			bool loopStep();

		private:
			uptr<ServicesManager> m_servicesManager;
			AppState m_state;
			uptr<IApp> m_iapp{ nullptr };
			uptr<EventManager> m_eventManager{ nullptr };
			sptr<Driver> m_driver{ nullptr };

			std::vector<uptr<AppService>> m_services;
		};
	}
}

#endif
