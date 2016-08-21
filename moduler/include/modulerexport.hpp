#ifndef MODULER_EXPORTS_HPP
#define MODULER_EXPORTS_HPP

#ifdef MODULER_EXPORTS
	#ifdef _WIN32
		#define MODULER_API   __declspec( dllexport ) 
	#else
		#define MODULER_API
	#endif
#else
	#ifdef _WIN32
		#define MODULER_API   __declspec( dllimport ) 
	#else
		#define MODULER_API
	#endif
#endif

#endif
