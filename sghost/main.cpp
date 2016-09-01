#include "memleakdetector.hpp"
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

	IModule *temp = moduler->loadModule("apprunnerd.dll");
//	LOG_DEBUG(std::string(temp!=nullptr?"true":"false").c_str());

	// Destroy the moduler
	destroyModuler();

	// Destroy the logger
	destroyLogger();
	finishMemLeakDetector();
	int result = 0;
	return result;
}
