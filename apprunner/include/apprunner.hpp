#ifndef APPRUNNER_INCLUDE_HPP
#define APPRUNNER_INCLUDE_HPP

#include "iapprunner.hpp"

namespace apprunner
{
	class AppRunner : public virtual IAppRunner
	{
	public:
		AppRunner();
		~AppRunner();

	};
}

#endif
