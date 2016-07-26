#include <lib/include/main.hpp>
#include <lib/core/compileconfig.hpp>
#include <lib/core/memmanager.hpp>
#include <lib/core/log.hpp>
#include <lib/core/hostcontroller.hpp>
#include <lib/core/paramparser.hpp>
#include <vector>
#include <string>

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

	int libMain(int argc, char *argv[])
	{
		int result = -1;

		try
		{
			initLog(false,false,false);
			installMemManager();
			core::ParamParser paramParser(argc, argv);
			core::HostController::createHostController(std::move(paramParser));
			auto hController = core::HostController::hController();
			hController->initialize();

			// WIP:
			hController->loadAppFromFileName("zoper");
			// End wip

			result = hController->run();
			hController->finalize();
			core::HostController::destroyHostController();
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
