#ifndef MODULER_IMODULE_EXPORT_INCLUDE_HPP
#define MODULER_IMODULE_EXPORT_INCLUDE_HPP

#include "imodule.hpp"

#define CREATE_MODULE_FUNC_NAME	createModule
#define DELETE_MODULE_FUNC_NAME	deleteModule

#define CREATE_MODULE_FUNC_NAME_STR	"createModule"
#define GET_MODULE_FUNC_NAME_STR	"getModule"
#define DELETE_MODULE_FUNC_NAME_STR "deleteModule"

#define DECLARE_MODULE_CREATION     \
	EXPORT_API bool createModule();     \
	EXPORT_API moduler::IModule* getModule();     \
    EXPORT_API bool deleteModule();

// Note: Use this define only in a not exported cpp/c file
#define DEFINE_MODULE_CREATION(className)     \
	static className *m_instance##className{nullptr};	\
	bool CREATE_MODULE_FUNC_NAME()	\
	{	\
		if (!m_instance##className)	{	\
			m_instance##className = new className;	\
			return true;	\
		}	\
		return false;	\
	}	\
	moduler::IModule* getModule() {return m_instance##className; }	\
    bool DELETE_MODULE_FUNC_NAME()	\
	{	\
		if (m_instance##className) {	\
			delete m_instance##className;	\
			m_instance##className = nullptr;	\
			return true;	\
		}	\
		return false;	\
	}

#endif
