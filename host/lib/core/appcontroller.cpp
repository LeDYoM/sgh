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
#include "servicesmanager.hpp"

namespace lib
{
	namespace core
	{
		AppController::AppController(uptr<IApp> iapp, sptr<Driver> driverInstance)
			: m_iapp{ std::move(iapp) }, m_driver{ driverInstance }, m_servicesManager{ new ServicesManager{ this } }
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
				m_servicesManager->addServiceInstance(uptr<ExceptionManager>{new ExceptionManager{} });
				m_servicesManager->addServiceInstance(uptr<FileSystem>{ new FileSystem{} });
				m_servicesManager->addServiceInstance(uptr<Configuration>{ new Configuration{} });
				m_servicesManager->addServiceInstance(uptr<EventManager>{ new EventManager{} });
				m_servicesManager->addServiceInstance(uptr<UtilProvider>{new UtilProvider{}});
				m_servicesManager->addServiceInstance(uptr<ResourceManager>{ new ResourceManager{} });
				m_servicesManager->addServiceInstance(uptr<draw::SceneManager>{ new draw::SceneManager{} });
				m_window = uptr<Window>{ new Window{ m_iapp->getAppDescriptor().wcp } };

				m_window->PrivateSetup(this);
				m_servicesManager->setupAllServices();
				m_servicesManager->initializeServices();

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
