#ifndef VTX_COMMON_DEFINITIONS_HPP
#define VTX_COMMON_DEFINITIONS_HPP

#define DECLARE_PRIVATE_PIMPL(className,privateObject)		private:	\
	struct className##Private;	\
	className##Private *privateObject;


#endif

