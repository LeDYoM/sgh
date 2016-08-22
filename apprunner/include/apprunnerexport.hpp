#ifndef APPRUNNER_EXPORTS_HPP
#define APPRUNNER_EXPORTS_HPP

#ifdef APPRUNNER_EXPORTS
	#ifdef _WIN32
		#define APPRUNNER_API   __declspec( dllexport ) 
	#else
		#define APPRUNNER_API
	#endif
#else
	#ifdef _WIN32
		#define APPRUNNER_API   __declspec( dllimport ) 
	#else
		#define APPRUNNER_API
	#endif
#endif

#endif
