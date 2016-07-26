#include "appcontroller.hpp"
#include "window.hpp"
#include "resourcemanager.hpp"
#include <lib/draw/scenemanager.hpp>
#include <lib/draw/rendermanager.hpp>
#include "utilprovider.hpp"
#include "log.hpp"
#include "exceptionmanager.hpp"
#include "filesystem.hpp"
#include "configuration.hpp"
#include "servicesmanager.hpp"
#include "shareddata.hpp"
#include "input.hpp"
#include "driver.hpp"

namespace lib
{
	namespace core
	{
		AppController::AppController(uptr<IApp> iapp, sptr<Driver> driverInstance)
			: m_iapp{ std::move(iapp) }, m_driver{ driverInstance }, m_servicesManager{ new ServicesManager{ this } }
		{
			LOG_CONSTRUCT_NOPARAMS;
			m_iapp->setAppContext(this);
			m_window = sptr<Window>{ new Window(this, driverInstance->currentWindow()) };
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
				LOG_DEBUG(appId() + ":  Starting initialization...");
				m_state = AppState::Executing;

				m_servicesManager->addService(sptr<ExceptionManager>{new ExceptionManager{}});
				m_servicesManager->addService(sptr<FileSystem>{ new FileSystem{} });
				m_servicesManager->addService(sptr<Configuration>{ new Configuration{} });
				m_servicesManager->addService(sptr<SharedData>{ new SharedData{} });
				m_servicesManager->addService(sptr<UtilProvider>{new UtilProvider{}});
				m_servicesManager->addService(sptr<ResourceManager>{ new ResourceManager{} });
				m_servicesManager->addService(sptr<draw::SceneManager>{ new draw::SceneManager{} });
				m_servicesManager->addService(sptr<draw::RenderManager>{ new draw::RenderManager{} });
				m_servicesManager->addService(sptr<Input>{new Input{}});

				m_servicesManager->setupAllServices();
				m_servicesManager->initializeServices();

				m_servicesManager->service<draw::SceneManager>()->addScenes(m_iapp->scenesVector());

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

				m_servicesManager->stopServices();
				LOG_DEBUG(appId() + ": terminated");
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
			m_servicesManager->service<draw::SceneManager>()->update();
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

		AppController * toController(PIAppContext context)
		{
			return dynamic_cast<AppController*>(context);
		}
	}
}
