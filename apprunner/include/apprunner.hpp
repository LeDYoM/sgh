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

		virtual moduler::ModuleInformation *const moduleInformation() const override;

		virtual bool start() override;
		virtual bool stop() override;

		virtual bool update() override;

	};
}

#endif
