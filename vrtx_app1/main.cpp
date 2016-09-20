#include <vortex/include/vortex.hpp>
#include <vortex/include/app.hpp>
#include <vortex/include/logger.hpp>

int main(int argc, char* argv[])
{
	using namespace vtx;

	Vortex *vortex{ Vortex::createInstance() };
	vortex->initialize();
	vortex->deinitialize();
	Vortex::destroyInstance();
	return 0;
}
