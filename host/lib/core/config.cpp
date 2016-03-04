#include "config.hpp"
#include "log.hpp"

namespace lib
{
	namespace core
	{
		Config::Config(AppController *const appController)
			: AppService{ appController }
		{
		}

		void Config::loadFile(const std::string &file)
		{

		}
	}
}
