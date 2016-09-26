#include "application.hpp"
#include <vortex/include/vortex.hpp>

int main(int argc, char* argv[])
{
	using namespace vtx;
	int result{ 0 };

	{
		Vortex_Init();
		//	auto pLogger (Logger::createInstance());
		//	pLogger->severity() = Logger::LogSeverity::Debug;
//		Application app;
		//	auto pVortex(Vortex::createInstance());
		//	pVortex->initialize();

//		result = app.execute();

		//	pVortex->deinitialize();
		//	Vortex::destroyInstance();

		//	pLogger->destroyInstance();
		Vortex_DeInit();
	}

	return result;
}
