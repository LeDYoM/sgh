#ifndef COMPILER_CONFIGURATION_HPP
#define COMPILER_CONFIGURATION_HPP

	#ifdef _WIN32

		// Windows
		#define VORTEX_SYSTEM_WINDOWS
		#ifdef vortex_EXPORTS
			#define VORTEX_API __declspec(dllexport)
		#else
			#define VORTEX_API __declspec(dllimport)
		#endif
	#else

		// For now, Linux
		#define VORTEX_SYSTEM_LINUX
		#define VORTEX_API __declspec(dllexport)

	#endif

#endif

