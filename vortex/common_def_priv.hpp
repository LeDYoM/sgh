#ifndef VTX_PRIVATE_COMMON_DEFINITIONS_HPP
#define VTX_PRIVATE_COMMON_DEFINITIONS_HPP

#define DELETE_PRIVATE_MPRIVATE_PIMPL(className)	DELETE_PRIVATE_PIMPL(className,m_private)

#define DELETE_PRIVATE_PIMPL(className,privateObject)	if (privateObject) {	\
		delete privateObject;	\
		privateObject = nullptr;	\
	}

#define PRIVATE_STRUCT_NAME(className)	className::className##Private
#endif

