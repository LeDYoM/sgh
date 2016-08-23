#include <logger/include/logger.hpp>
#include <moduler/include/moduler.hpp>

#include <apprunner/include/iapprunner.hpp>

#include <string>

int main(int argc, char* argv[])
{
	using namespace logger;
	using namespace moduler;
	createLogger();
	auto *moduler = createModuler();
	IModule *temp = moduler->loadModule("apprunnerd.dll");
	LOG_DEBUG(std::string(temp!=nullptr?"true":"false").c_str());
	destroyModuler();
	destroyLogger();
	int result = 0;
	return result;
}
