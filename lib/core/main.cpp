#include <lib/include/main.hpp>
#include <lib/core/compileconfig.hpp>
#include <lib/core/memmanager.hpp>
#include <lib/core/log.hpp>
#include <lib/core/hostcontroller.hpp>
#include <vector>
#include <string>

// Temp
#include "../../host/zoperprogramcontroller.hpp"

namespace lib
{
	namespace
	{
		std::vector<std::string> transformParams(int argc, char *argv[])
		{
			std::vector<std::string> temp;

			for (int i=1;i<argc;++i)
			{
				temp.push_back(argv[i]);
			}
			return temp;
		}
	}

	int lib::libMain(int argc, char *argv[], uptr<lib::IApp> iApp)
	{
		argc;
		argv;
		int result = -1;

		try
		{
			initLog();
			installMemManager();
			zoper::ZoperProgramController *program = new zoper::ZoperProgramController;

			core::HostController hostController(transformParams(argc,argv));
			// WIP:
			hostController.initialize();
//			uptr<IApp> zpc = std::make_unique<zoper::ZoperProgramController>();
			hostController.addApp(std::move(iApp));

			// End wip
			result = hostController.run();
			hostController.finalize();
		}
		catch (std::exception e)
		{
			LOG_DEBUG("Exception: " << e.what());
		}
		finishMemManager();
		finishLog();

		return result;
	}
}
/*
int main(int argc, char* argv[])
{
	int result = lib::libMain(argc, argv, lib::uptr<lib::IApp>(new zoper::ZoperProgramController));
	return result;
}
*/
int main(int argc, char* argv[])
{
	lib::libMain(argc, argv, nullptr);
	return 0;
}
