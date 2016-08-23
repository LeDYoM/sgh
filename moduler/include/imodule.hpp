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

#define DECLARE_MODULE_CREATION()     \
	EXPORT_API moduler::IModule* createModule();     \
    EXPORT_API bool deleteModule(moduler::IModule*);

#define DEFINE_MODULE_CREATION(className)     \
	moduler::IModule* createModule()	\
	{	\
		return new className;	\
	}	\
    bool deleteModule(moduler::IModule*module)	\
	{	\
		if (module) {	\
			delete module;	\
			return true;	\
		}	\
		return false;	\
	}

#endif
