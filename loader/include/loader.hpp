#ifndef LOADER_INCLUDE_HPP
#define LOADER_INCLUDE_HPP

#include "loaderexport.hpp"

namespace loader
{
	class LoaderPrivate;
	class Loader
	{
	public:
		Loader();
		~Loader();

	private:
		LoaderPrivate *m_private;
	};

	LOADER_API Loader *createLoader();
	LOADER_API void destroyLoader();

}


#endif
