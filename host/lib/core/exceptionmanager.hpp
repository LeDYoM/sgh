#ifndef LIB_FILE_HPP
#define LIB_FILE_HPP

#include <lib/include/types.hpp>
#include "appservice.hpp"
#include <string>

namespace lib
{
	namespace core
	{
		class ExceptionManager : public AppService
		{
		public:
			ExceptionManager(AppController *const appController);
			virtual ~ExceptionManager();
		private:
		};
	}
}
#endif
