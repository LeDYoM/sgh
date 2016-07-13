#include <lib/include/main.hpp>
#include <lib/core/compileconfig.hpp>
#include <lib/core/memmanager.hpp>
#include <lib/core/log.hpp>
#include <lib/core/hostcontroller.hpp>
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

	int lib::libMain(int argc, char *argv[])
	{
		argc;
		argv;
		int result = -1;

		try
		{
			initLog();
			installMemManager();

			core::HostController hostController(transformParams(argc,argv));
			hostController.initialize();

			// WIP:
			hostController.loadAppFromFileName("zoper");
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
