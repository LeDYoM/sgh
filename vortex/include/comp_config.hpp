#ifndef VTX_COMPILER_CONFIGURATION_HPP
#define VTX_COMPILER_CONFIGURATION_HPP

	#ifdef _WIN32

		// Windows
		#define VORTEX_SYSTEM_WINDOWS
		#ifdef vortex_EXPORTS
			#define VORTEX_API __declspec(dllexport)
			#define EXPIMP_TEMPLATE
		#else
			#define VORTEX_API __declspec(dllimport)
			#define EXPIMP_TEMPLATE extern
		#endif
	#else

		// For now, Linux
		#define VORTEX_SYSTEM_LINUX
		#define VORTEX_API __declspec(dllexport)

	#endif

#endif

