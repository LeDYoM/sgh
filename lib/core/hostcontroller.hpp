#ifndef __LIB_HOSTCONTROLLER_HPP__
#define __LIB_HOSTCONTROLLER_HPP__

#include <lib/core/vecsptr.hpp>
#include <lib/include/iapp.hpp>

#include "paramparser.hpp"

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

		class HostController
		{
		public:
			HostController(int argc, char *argv[]);
			virtual ~HostController();

			int initialize();
			int run();
			int finalize();

			void loadAppFromFileName(const str&fileName);
		private:
			void addApp(uptr<IApp> iapp);
			void addTask(sptr<HostTask> newTask);
			void removeApp(sptr<AppController> iapp);

			void processTask();
			sptr<Window> m_window{ nullptr };
			bool exit{ false };
			std::queue<sptr<HostTask>> m_pendingTasks;
			VecSPtr<AppController> m_apps;
			sptr<Driver> m_driver{ nullptr };
			ParamParser m_paramParser;
		};
	}
}

#endif
