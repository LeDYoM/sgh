#include "include/loader.hpp"
#include <moduler/include/moduler.hpp>
#include <logger/include/logger.hpp>

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
		LOG_DEBUG("Creating loader...");
		if (!loaderInstance)
			loaderInstance = new Loader;

		LOG_DEBUG("Loader created");

		return loaderInstance;
	}

	void destroyLoader()
	{
		if (loaderInstance)
		{
			LOG_DEBUG("Destroying loader...");
			delete loaderInstance;
			loaderInstance = nullptr;
			LOG_DEBUG("Loader destroyed");
		}
	}
}
