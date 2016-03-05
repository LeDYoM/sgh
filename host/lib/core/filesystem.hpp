#ifndef LIB_FILESYSTEM_HPP
#define LIB_FILESYSTEM_HPP

#include <lib/include/types.hpp>
#include "appservice.hpp"

namespace lib
{
	namespace core
	{
		class FileSystem : public AppService
		{
		public:
			FileSystem(AppController *const appController);
			virtual ~FileSystem();

		};
	}
}
#endif
