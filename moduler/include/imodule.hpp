#ifndef MODULER_IMODULE_INTERFACE_INCLUDE_HPP
#define MODULER_IMODULE_INTERFACE_INCLUDE_HPP

#include "ibasicinterface.hpp"

namespace moduler
{
	class IModule : public virtual IBasicInterface
	{
	public:
		IModule() {}
		virtual ~IModule() {}
	};
}

#endif
