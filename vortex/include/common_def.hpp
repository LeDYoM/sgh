#ifndef VTX_COMMON_DEFINITIONS_HPP
#define VTX_COMMON_DEFINITIONS_HPP

#define DECLARE_PRIVATE_PIMPL(className,privateObject)		private:	\
	struct className##Private;	\
	className##Private *privateObject;

#define DECLARE_PRIVATE_MPRIVATE_PIMPL(className)		DECLARE_PRIVATE_PIMPL(className,m_private)


#endif

