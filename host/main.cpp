#include <lib/include/main.hpp>

#include "zoperprogramcontroller.hpp"

int main(int argc, char* argv[])
{
	int result = lib::libMain(argc, argv,lib::uptr<lib::IApp>(new zoper::ZoperProgramController));
	return result;
}
