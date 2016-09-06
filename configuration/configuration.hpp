#ifndef FILESYSTEM_INCLUDE_HPP
#define FILESYSTEM_INCLUDE_HPP

#include "include/iconfiguration.hpp"

namespace configuration
{
	class Configuration : public virtual IConfiguration
	{
	public:
		Configuration();
		~Configuration();

		virtual moduler::ModuleInformation *const moduleInformation() const override;

		virtual bool start() override;
		virtual bool stop() override;
	};
}

#endif
