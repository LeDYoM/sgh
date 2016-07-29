#include "hostcontroller.hpp"
#include "wcp.hpp"
#include "window.hpp"
#include "log.hpp"
#include "hosttask.hpp"
#include "appcontroller.hpp"
#include "driver.hpp"

//Temp
#include "../../host/zoperprogramcontroller.hpp"

namespace lib
{
	namespace core
	{
		namespace priv
		{
			struct HostConfiguration
			{
				WindowCreationParams wcp;
				bool log2Console{ true };
				bool log2File{ false };
				bool log2Ide{ true };

				void setDataMap(const DataMap& map)
				{
					wcp.size = fromDataMap<u32>(map, { "rx", "ry" });
				}
			};
		}

		HostController *HostController::instance{ nullptr };


		HostController::HostController(
#ifdef _ACCEPT_CONFIGURATION_PARAMETERS_
			ParamParser &&paramParser
#endif
		)
			: m_configuration{new priv::HostConfiguration }
#ifdef _ACCEPT_CONFIGURATION_PARAMETERS_
			, m_paramParser{paramParser}
#endif
		{
			LOG_CONSTRUCT_NOPARAMS;
			LOG_INFO("Starting HostController...");
		}

		HostController::~HostController()
		{
			LOG_DESTRUCT_NOPARAMS;
		}

		void HostController::createHostController(
#ifdef _ACCEPT_CONFIGURATION_PARAMETERS_
			ParamParser &&paramParser
#endif
		)
		{
			__CRITICAL(!instance, "Cannot start more than one host controller");
			instance = new HostController(
#ifdef _ACCEPT_CONFIGURATION_PARAMETERS_
				std::move(paramParser)
#endif
			);
		}

		void HostController::destroyHostController()
		{
			__ASSERT(instance, "There is no instance of the hostcontroller");
			delete instance;
			instance = nullptr;
		}

		int HostController::initialize()
		{
			// Temporary hardcoded initialization
			loadConfiguration();

			addTask(sptr<HostTaskLoadDriver>(new HostTaskLoadDriver("fooDriver.dll")));
			return 0;
		}

		int HostController::run()
		{
			// TO DO: Do initialize here.
			// initialize();
			while (!exit)
			{
				processTask();
				exit = m_apps.empty();
				for (auto appNode : m_apps)
				{
					bool terminated = appNode->update();
					if (terminated)
					{
						removeApp(appNode);
					}
				}
			}

			if (m_apps.empty())
			{
				LOG_INFO("Apps list is empty. Exiting normally");
			}
			return 0;
		}

		int HostController::finalize()
		{
			addTask(sptr<HostTaskUnloadDriver>(new HostTaskUnloadDriver()));
			processTask();
			return 0;
		}

		void HostController::loadAppFromFileName(const str&fileName)
		{
			addTask(sptr<HostTaskLoadAppFromFileName>(new HostTaskLoadAppFromFileName(fileName)));
			// Temp. Ignore filename.
			addApp(getModule());
		}

		void HostController::addApp(uptr<IApp> iapp)
		{
			__ASSERT(iapp, "Trying to add null application");
			if (iapp) addTask(sptr<HostTaskLoadAppFromIApp>(new HostTaskLoadAppFromIApp(std::move(iapp))));
		}

		void HostController::removeApp(sptr<AppController> iapp)
		{
			addTask(sptr<HostTaskUnloadApp>(new HostTaskUnloadApp(iapp)));
		}

		void HostController::loadConfiguration()
		{
#ifdef _ACCEPT_CONFIGURATION_PARAMETERS_
			m_configuration->setDataMap(m_paramParser.parameters());
#endif

			if (m_configuration->wcp.size.x < 1 || m_configuration->wcp.size.y < 1)
			{
				m_configuration->wcp.size = vector2du32{ 1024,768 };
			}
		}

		void HostController::addTask(sptr<HostTask> newTask)
		{
			m_pendingTasks.push(newTask);
		}

		void HostController::processTask()
		{
			if (!m_pendingTasks.empty()) {
				u32 nTasks = m_pendingTasks.size();
				u32 nProcessedTasks{ 0 };
				while (nProcessedTasks < nTasks && !m_pendingTasks.empty())
				{
					auto task = m_pendingTasks.front();
					switch (task->code())
					{
					case HostTask::HostTaskCode::LoadDriver:
						__ASSERT(!m_driver, "Cannot load another driver. There is already one loaded");
						m_driver = sptr<Driver>{new Driver};
						m_driver->initialize("");
						m_driver->newWindow(m_configuration->wcp);
						break;
					case HostTask::HostTaskCode::UnloadDriver:
						__ASSERT(m_driver, "Trying to delete driver when no driver loaded");
						m_driver.reset();
						break;
					case HostTask::HostTaskCode::LoadAppFromFileName:
						__ASSERT(m_driver, "Cannot load an app without having loaded a driver first");
						break;
					case HostTask::HostTaskCode::LoadAppFromIApp:
					{
						__ASSERT(m_driver, "Cannot load an app without having loaded a driver first");
						sptr<AppController> app = sptr<AppController>(new AppController
							(std::move(std::dynamic_pointer_cast<HostTaskLoadAppFromIApp>(task)->deAttach()), m_driver));
						m_apps.push_back(app);
					}
					break;
					case HostTask::HostTaskCode::UnloadApp:
					{
						sptr<AppController> app{ std::dynamic_pointer_cast<HostTaskUnloadApp>(task)->deAttach() };
						bool found{ removeFromspVector(app, m_apps) };
						if (found) {
							LOG_DEBUG("Going to uninstatiate " << app->appId());
							app.reset();
						}
						else {
							LOG_WARNING("Trying to unload unregistered app");
						}
					}
					break;
					default:
						break;
					}
					m_pendingTasks.pop();
					++nProcessedTasks;
				}
			}
		}

	}
}
