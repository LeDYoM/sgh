#include "appcontroller.hpp"
#include "window.hpp"
#include "resourcemanager.hpp"
#include <lib/draw/scenemanager.hpp>
#include <lib/draw/scene.hpp>
#include <lib/util/utilprovider.hpp>
#include "log.hpp"
#include "eventmanager.hpp"
#include "exceptionmanager.hpp"
#include "filesystem.hpp"
#include "config.hpp"

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
			LOG_DESTRUCT("Name: " << appId());
		}

		bool AppController::update()
		{
			switch (m_state)
			{
			case lib::core::AppController::AppState::NotInitialized:
				break;
			case lib::core::AppController::AppState::ReadyToStart:
			{
				// Create the scene manager
				LOG_DEBUG_(appId() + ":  Starting initialization...");
				m_state = AppState::Executing;

				//TO DO: Ask via requests
				m_exceptionManager = uptr<ExceptionManager>{ new ExceptionManager{} };
				m_fileSystem = uptr<FileSystem>{ new FileSystem{} };
				m_config = uptr<Config>{ new Config{} };
				m_eventManager = uptr<EventManager>{ new EventManager{} };
				m_utilProvider = uptr<util::UtilProvider>{new util::UtilProvider{}};
				m_window = uptr<Window>{ new Window{m_iapp->getAppDescriptor().wcp} };
				m_resourceManager = uptr<ResourceManager>{ new ResourceManager{} };
				m_sceneManager = uptr<draw::SceneManager>{ new draw::SceneManager{} };

				m_exceptionManager->PrivateInit(this);
				m_fileSystem->PrivateInit(this);
				m_config->PrivateInit(this);
				m_eventManager->PrivateInit(this);
				m_utilProvider->PrivateInit(this);
				m_window->PrivateInit(this);
				m_resourceManager->PrivateInit(this);
				m_sceneManager->PrivateInit(this);

				m_config->loadFile(m_fileSystem->getFile(m_iapp->getAppDescriptor().configFile));
				m_sceneManager->addScenes(m_iapp->scenesVector());

				m_iapp->onInit();
				LOG_DEBUG(appId() << ": " << " is now executing");
			}
				break;
			case lib::core::AppController::AppState::Executing:
			{
				if (loopStep())
				{
					m_state = AppState::ReadyToTerminate;
					LOG_DEBUG(appId() << ": " << " is now ready to terminate");
				}
			}
				break;
			case lib::core::AppController::AppState::ReadyToTerminate:
				LOG_DEBUG(appId() << ": " << " started termination");
				m_state = AppState::Terminated;
//				m_iapp->onFinish();

				m_sceneManager = nullptr;
				m_resourceManager = nullptr;
				m_window = nullptr;
				m_utilProvider = nullptr;
				m_eventManager = nullptr;
				m_config = nullptr;
				m_fileSystem = nullptr;
				m_exceptionManager = nullptr;
				LOG_DEBUG_(appId() + ": terminated");
				return true;
				break;
			case lib::core::AppController::AppState::Terminated:
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
