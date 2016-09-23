#include <vortex/include/vortex.hpp>
#include <vortex/include/iapplication.hpp>
#include <vortex/include/logger.hpp>

int main(int argc, char* argv[])
{
	using namespace vtx;

	auto pLogger (Logger::createInstance());
	pLogger->severity() = Logger::LogSeverity::Debug;
	auto pVortex(Vortex::createInstance());
	pVortex->initialize();
	pVortex->deinitialize();
	Vortex::destroyInstance();
	return 0;
}
