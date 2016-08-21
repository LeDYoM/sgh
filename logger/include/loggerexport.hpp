#ifndef LOGGER_EXPORTS_HPP
#define LOGGER_EXPORTS_HPP

#ifdef LOGGER_EXPORTS
	#ifdef _WIN32
		#define LOGGER_API   __declspec( dllexport ) 
	#else
		#define LOGGER_API
	#endif
#else
	#ifdef _WIN32
		#define LOGGER_API   __declspec( dllimport ) 
	#else
		#define LOGGER_API
	#endif
#endif

#endif
