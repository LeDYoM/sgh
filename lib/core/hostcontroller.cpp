#include "hostcontroller.hpp"
#include "window.hpp"
#include "log.hpp"
#include "hosttask.hpp"
#include "appcontroller.hpp"
#include "driver.hpp"

namespace lib
{
	namespace core
	{
		HostController::HostController(const std::vector<std::string> &params)
//			: Configuration{ "host.cfg" }
		{
			params;
			LOG_CONSTRUCT_NOPARAMS;
			LOG_INFO("Starting HostController...");
		}

		HostController::~HostController()
		{
			LOG_DESTRUCT_NOPARAMS;
		}

		int HostController::initialize()
		{
			// Temporary hardcoded initialization
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
				for (auto app : m_apps)
				{
					bool terminated = app->update();
					if (terminated)
					{
						removeApp(app);
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

		void HostController::addApp(uptr<IApp> iapp)
		{
			addTask(sptr<HostTaskLoadAppFromIApp>(new HostTaskLoadAppFromIApp(std::move(iapp))));
		}

		void HostController::removeApp(sptr<AppController> iapp)
		{
			addTask(sptr<HostTaskUnloadApp>(new HostTaskUnloadApp(iapp)));
		}

		void HostController::addTask(sptr<HostTask> newTask)
		{
			m_pendingTasks.push(newTask);
		}

		void HostController::processTask()
		{
			if (!m_pendingTasks.empty())
			{
				u32 nTasks = m_pendingTasks.size();
				u32 nProcessedTasks{ 0 };
				while (nProcessedTasks < nTasks && !m_pendingTasks.empty())
				{
					auto task = m_pendingTasks.front();
					switch (task->code())
					{
					case HostTask::HostTaskCode::LoadDriver:
						__ASSERT(!m_driver, "Cannot load another driver. There is already one loaded");
						m_driver = sptr<Driver>(new Driver());
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
						if (found)
						{
							LOG_DEBUG("Going to uninstatiate " << app->appId());
							app.reset();
						}
						else
						{
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
