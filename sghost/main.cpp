#include <logger/include/logger.hpp>
#include <loader/include/loader.hpp>

#include <apprunner/include/iapprunner.hpp>

#include <string>

int main(int argc, char* argv[])
{
	using namespace logger;
	using namespace loader;
	createLogger();
	auto *loader = createLoader();
	IModule *temp = loader->loadModule("apprunnerd.dll");
	LOG_DEBUG(std::string(temp!=nullptr?"true":"false").c_str());
	destroyLoader();
	destroyLogger();
	int result = 0;
	return result;
}
