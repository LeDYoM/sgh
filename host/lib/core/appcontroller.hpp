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
			uptr<Window> const &parentWindow() const { return m_window; }
			uptr<ResourceManager> const &resourceManager() const { return m_resourceManager; }
			uptr<EventManager> const &eventManager() const { return m_eventManager; }
			uptr<UtilProvider> const &utilProvider() const { return m_utilProvider; }
			uptr<ExceptionManager> const &exceptionManager() const { return m_exceptionManager; }
			uptr<FileSystem> const &fileSystem() const { return m_fileSystem; }
			uptr<Configuration> const &configuration() const { return m_configuration; }
			sptr<Driver> const &driver() const { return m_driver; }

			const std::string appId() const;

		protected:
			bool loopStep();

		private:
			uptr<ServicesManager> m_servicesManager;
			AppState m_state;
			uptr<Window> m_window{ nullptr };
			uptr<IApp> m_iapp{ nullptr };
			uptr<Configuration> m_configuration{ nullptr };
			uptr<draw::SceneManager> m_sceneManager{ nullptr };
			uptr<ResourceManager> m_resourceManager{ nullptr };
			uptr<EventManager> m_eventManager{ nullptr };
			uptr<UtilProvider> m_utilProvider{ nullptr };
			uptr<ExceptionManager> m_exceptionManager{ nullptr };
			uptr<FileSystem> m_fileSystem{ nullptr };
			sptr<Driver> m_driver{ nullptr };

			std::vector<uptr<AppService>> m_services;
		};
	}
}

#endif
