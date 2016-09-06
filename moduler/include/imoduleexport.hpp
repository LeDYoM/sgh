#ifndef MODULER_IMODULE_EXPORT_INCLUDE_HPP
#define MODULER_IMODULE_EXPORT_INCLUDE_HPP

#include "imodule.hpp"

#define CREATE_MODULE_FUNC_NAME		createModule
#define GET_MODULE_FUNC_NAME		getModule
#define DELETE_MODULE_FUNC_NAME		deleteModule

#define CREATE_MODULE_FUNC_NAME_STR	"createModule"
#define GET_MODULE_FUNC_NAME_STR	"getModule"
#define DELETE_MODULE_FUNC_NAME_STR "deleteModule"

#if !defined MODULER_EXPORTS && defined WIN32
	#define EXPORT_API   extern "C" __declspec( dllexport ) 
#else
	#define EXPORT_API
#endif

#ifndef MODULE_EXPORTS

#define DECLARE_MODULE_INFORMATION_BEGIN				static moduler::ModuleInformation moduleInfo =	{
#define DECLARE_MODULE_INFORMATION_NAME(name)				#name
#define DECLARE_MODULE_INFORMATION_VERSION(v)				#v
#define DECLARE_MODULE_INFORMATION_SUBVERSION(v)			#v
#define DECLARE_MODULE_INFORMATION_PATCH(v)					#v
#define DECLARE_MODULE_INFORMATION_END					};
#define DECLARE_MODULE_INFORMATION_GETTER(className)	moduler::ModuleInformation * const className::moduleInformation() const	\
														{	\
															return &moduleInfo;	\
														}

#define DECLARE_MODULE_CREATION		\
	EXPORT_API bool CREATE_MODULE_FUNC_NAME();	\
	EXPORT_API moduler::IModule* GET_MODULE_FUNC_NAME();	\
	EXPORT_API bool DELETE_MODULE_FUNC_NAME();

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

#endif
