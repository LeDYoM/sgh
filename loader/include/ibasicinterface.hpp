#ifndef LOADER_BASIC_INTERFACE_INCLUDE_HPP
#define LOADER_BASIC_INTERFACE_INCLUDE_HPP

#ifndef LOADER_EXPORTS
	#ifdef _WIN32
		#define EXPORT_API   __declspec( dllexport ) 
	#else
		#define EXPORT_API
	#endif
#else
	#define EXPORT_API
#endif


namespace loader
{
	class IBasicInterface
	{
	public:
		IBasicInterface() {}
		virtual ~IBasicInterface() {}

	};
}

#endif
