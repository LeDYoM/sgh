#include "memleakdetector.hpp"
#include "hostmodule.hpp"
#include <logger/include/logger.hpp>
#include <moduler/include/moduler.hpp>
#include <string>

int main(int argc, char* argv[])
{
	installMemLeakDetector();
	// Create and initialize the logging
	using namespace logger;
	createLogger()->setLoggerSeverity(LogSeverity::Debug);

	// Create and initialize the moduler
	using namespace moduler;
	auto *moduler = createModuler();

	HostModule *hostModule = new HostModule;
	moduler->addDirectModule(new HostModule);
//	IModule *temp = 
//		moduler->loadModule("apprunnerd.dll");

	// Destroy the moduler
	destroyModuler();
	delete hostModule;

	// Destroy the logger
	destroyLogger();
	finishMemLeakDetector();
	int result = 0;
	return result;
}
