#include <logger/include/logger.hpp>
#include <loader/include/loader.hpp>

int main(int argc, char* argv[])
{
	using namespace logger;
	using namespace loader;
	createLogger();
	auto *loader = createLoader();
	destroyLoader();
	destroyLogger();
	int result = 0;
	return result;
}
