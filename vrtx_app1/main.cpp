#include "application.hpp"
#include <vortex/include/vortex.hpp>
#include <memory>

int main(int argc, char* argv[])
{
	using namespace vtx;
	int result{ 0 };

	{
		Vortex_Init();
		Vortex::getInstance()->setApplication(new VApplication{});
		//	auto pLogger (Logger::createInstance());
		//	pLogger->severity() = Logger::LogSeverity::Debug;
//		Application app;
		//	auto pVortex(Vortex::createInstance());
		//	pVortex->initialize();

		result = Vortex_Loop();

		//	pVortex->deinitialize();
		//	Vortex::destroyInstance();

		//	pLogger->destroyInstance();
		Vortex_DeInit();
	}

	return result;
}
