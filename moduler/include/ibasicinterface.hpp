#ifndef MODULER_BASIC_INTERFACE_INCLUDE_HPP
#define MODULER_BASIC_INTERFACE_INCLUDE_HPP

#ifndef MODULER_EXPORTS
	#ifdef _WIN32
		#define EXPORT_API   extern "C" __declspec( dllexport ) 
	#else
		#define EXPORT_API
	#endif
#else
	#define EXPORT_API
#endif

namespace moduler
{
	class IBasicInterface
	{
	public:
		IBasicInterface() {}
		virtual ~IBasicInterface() {}

	};
}

#endif
