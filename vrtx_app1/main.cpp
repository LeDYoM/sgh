#include "application.hpp"
#include <vortex/include/logger.hpp>

int main(int argc, char* argv[])
{
	using namespace vtx;

	auto pLogger (Logger::createInstance());
	pLogger->severity() = Logger::LogSeverity::Debug;
	Application app;
//	auto pVortex(Vortex::createInstance());
//	pVortex->initialize();

	int result(app.execute());

//	pVortex->deinitialize();
//	Vortex::destroyInstance();

	pLogger->destroyInstance();
	return result;
}
