#ifndef LOADER_IMODULE_INTERFACE_INCLUDE_HPP
#define LOADER_IMODULE_INTERFACE_INCLUDE_HPP

#include "ibasicinterface.hpp"

namespace loader
{
	class IModule : public virtual IBasicInterface
	{
	public:
		IModule() {}
		virtual ~IModule() {}
	};
}

#define DECLARE_MODULE_CREATION()     \
	EXPORT_API loader::IModule* createModule();     \
    EXPORT_API bool deleteModule(loader::IModule*);

#define DEFINE_MODULE_CREATION(className)     \
	loader::IModule* createModule()	\
	{	\
		return new className;	\
	}	\
    bool deleteModule(loader::IModule*module)	\
	{	\
		if (module) {	\
			delete module;	\
			return true;	\
		}	\
		return false;	\
	}

#endif
