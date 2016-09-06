#ifndef CONFIGURATION_INTERFACE_INCLUDE_HPP
#define CONFIGURATION_INTERFACE_INCLUDE_HPP

#include <moduler/include/imoduleexport.hpp>

namespace configuration
{
	class IConfiguration : public virtual moduler::IModule
	{
	public:
		IConfiguration() {}
		virtual ~IConfiguration() {}
	};
}

DECLARE_MODULE_CREATION

#endif
