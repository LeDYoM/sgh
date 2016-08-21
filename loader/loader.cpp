#include "include/loader.hpp"
#include <moduler/include/moduler.hpp>

namespace loader
{
	static Loader *loaderInstance{ nullptr };

	class LoaderPrivate
	{
	public:
		LoaderPrivate() {}
		~LoaderPrivate() {}
	};

	Loader::Loader()
	{
		m_private = new LoaderPrivate;
		moduler::createModuler();
	}

	Loader::~Loader()
	{
		moduler::destroyModuler();
		delete m_private;
	}

	Loader *createLoader()
	{
		if (!loaderInstance)
			loaderInstance = new Loader;

		return loaderInstance;
	}

	void destroyLoader()
	{
		if (loaderInstance)
		{
			delete loaderInstance;
			loaderInstance = nullptr;
		}
	}
}
