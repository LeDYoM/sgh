#include "appcontroller.hpp"
#include "window.hpp"
#include "resourcemanager.hpp"
#include <lib/draw/scenemanager.hpp>
#include <lib/draw/scene.hpp>
#include "utilprovider.hpp"
#include "log.hpp"
#include "eventmanager.hpp"
#include "exceptionmanager.hpp"
#include "filesystem.hpp"
#include "configuration.hpp"

namespace lib
{
	namespace core
	{
		AppController::AppController(uptr<IApp> iapp, sptr<Driver> driverInstance)
			: m_iapp{ std::move(iapp) }, m_driver{ driverInstance }
		{
			LOG_CONSTRUCT_NOPARAMS;
			LOG_DEBUG("Starting app " << appId() << "...");
			m_state = AppState::ReadyToStart;
		}

		AppController::~AppController()
		{
			LOG_DESTRUCT("Name: " + appId());
		}

		bool AppController::update()
		{
			switch (m_state)
			{
			case AppState::NotInitialized:
				break;
			case AppState::ReadyToStart:
			{
				// Create the scene manager
				LOG_DEBUG_(appId() + ":  Starting initialization...");
				m_state = AppState::Executing;

				//TO DO: Ask via requests
				addServiceInstance(uptr<ExceptionManager>{new ExceptionManager{} });
				addServiceInstance(uptr<FileSystem>{ new FileSystem{} });
				addServiceInstance(uptr<Configuration>{ new Configuration{} });
				addServiceInstance(uptr<EventManager>{ new EventManager{} });
				addServiceInstance(uptr<UtilProvider>{new UtilProvider{}});
				addServiceInstance(uptr<ResourceManager>{ new ResourceManager{} });
				addServiceInstance(uptr<draw::SceneManager>{ new draw::SceneManager{} });
				m_window = uptr<Window>{ new Window{ m_iapp->getAppDescriptor().wcp } };

				m_window->PrivateSetup(this);
				setupAllServices();

				initializeServices();

//				m_configuration->loadFile(/*m_fileSystem->getFile(*/m_iapp->getAppDescriptor().configFile/*)*/);
				m_configuration->loadConfiguration();
				m_resourceManager->load("*");
				m_sceneManager->addScenes(m_iapp->scenesVector());

				m_iapp->onInit();
				LOG_DEBUG(appId() << ": " << " is now executing");
			}
				break;
			case AppState::Executing:
			{
				if (loopStep())
				{
					m_state = AppState::ReadyToTerminate;
					LOG_DEBUG(appId() << ": " << " is now ready to terminate");
				}
			}
				break;
			case AppController::AppState::ReadyToTerminate:
				LOG_DEBUG(appId() << ": " << " started termination");
				m_state = AppState::Terminated;
//				m_iapp->onFinish();

				m_sceneManager = nullptr;
				m_resourceManager = nullptr;
				m_window = nullptr;
				m_utilProvider = nullptr;
				m_eventManager = nullptr;
				m_configuration = nullptr;
				m_fileSystem = nullptr;
				m_exceptionManager = nullptr;
				LOG_DEBUG_(appId() + ": terminated");
				return true;
				break;
			case AppState::Terminated:
				return true;
				break;
			default:
				break;
			}
			return false;
		}

		bool AppController::loopStep()
		{
			bool windowWants2Close = m_window->preLoop();
			m_eventManager->update();
			m_sceneManager->update();
			windowWants2Close |= m_window->postLoop();
			return windowWants2Close;
		}

		void AppController::addServiceInstance(uptr<AppService> newService)
		{
			m_services.push_back(std::move(newService));
		}

		void AppController::setupAllServices()
		{
			for (auto &service : m_services)
			{
				service->PrivateSetup(this);
			}
		}

		void AppController::initializeServices()
		{
			for (auto &service : m_services)
			{
				service->Init();
			}
		}

		const std::string AppController::appId() const
		{
			if (m_iapp)
			{
				return std::string(m_iapp->getAppDescriptor().Name + ":" + std::to_string(m_iapp->getAppDescriptor().Version) +
					"." + std::to_string(m_iapp->getAppDescriptor().SubVersion) + "."+std::to_string(m_iapp->getAppDescriptor().Patch));
			}
			return "NoApp:0.0.0";
		}

	}
}
