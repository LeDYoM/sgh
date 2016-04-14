#ifndef __LIB_MAIN_HPP__
#define __LIB_MAIN_HPP__

#include "compconfig.hpp"
#include "types.hpp"
#include "iapp.hpp"

namespace lib
{
	LIB_API_EXPORT int libMain(int argc, char *argv[], uptr<IApp> iApp);
}

#endif
