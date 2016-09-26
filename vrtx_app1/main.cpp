#include "application.hpp"
#include <vortex/include/vortex.hpp>
#include <memory>

int main(int argc, char* argv[])
{
	using namespace vtx;
	int result{ 0 };

	Vortex_Init();
	Vortex::getInstance()->setApplication(new Application);
	result = Vortex_Loop();
	Vortex_DeInit();

	return result;
}
