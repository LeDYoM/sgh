#ifndef __LIB_HOSTCONTROLLER_HPP__
#define __LIB_HOSTCONTROLLER_HPP__

#include "compileconfig.hpp"
#include <lib/core/vecsptr.hpp>
#include <lib/include/iapp.hpp>

#ifdef _ACCEPT_CONFIGURATION_PARAMETERS_
	#include "paramparser.hpp"
#endif

#include <queue>
#include <string>

namespace lib
{
	namespace core
	{
		class Window;
		class Driver;
		class HostTask;
		class AppController;
		namespace priv
		{
			struct HostPrivate;
		}

		class HostController
		{
		public:
			static void createHostController(
				#ifdef _ACCEPT_CONFIGURATION_PARAMETERS_
					ParamParser &&paramParser
				#endif
			);
			static void destroyHostController();
			static inline HostController *const hController() { return instance; }
			int initialize();
			int run();
			int finalize();

			void loadAppFromFileName(const str&fileName);
		private:
			HostController(
#ifdef _ACCEPT_CONFIGURATION_PARAMETERS_
				ParamParser &&paramParser
#endif
			);
			virtual ~HostController();

			static HostController *instance;
			void addApp(uptr<IApp> iapp);
			void addTask(sptr<HostTask> newTask);
			void removeApp(sptr<AppController> iapp);
			void loadConfiguration();

			void processTask();
			sptr<Window> m_window{ nullptr };
			bool exit{ false };
			std::queue<sptr<HostTask>> m_pendingTasks;
			VecSPtr<AppController> m_apps;
			sptr<Driver> m_driver{ nullptr };
#ifdef _ACCEPT_CONFIGURATION_PARAMETERS_
			ParamParser &m_paramParser;
#endif
			uptr<priv::HostPrivate> m_hPrivate;
		};
	}
}

#endif
