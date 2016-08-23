#include "include/loader.hpp"
#include <moduler/include/moduler.hpp>
#include <logger/include/logger.hpp>

namespace loader
{
	static Loader *loaderInstance{ nullptr };

	class LoaderPrivate
	{
	public:
		moduler::Moduler *modulerInstance{ nullptr };

		LoaderPrivate()
			: modulerInstance{ moduler::createModuler() } {}

		~LoaderPrivate() { moduler::destroyModuler(); }
	};

	Loader::Loader()
	{
		m_private = new LoaderPrivate;
		
	}

	Loader::~Loader()
	{
		delete m_private;
	}

	IModule * Loader::loadModule(const char * fileName)
	{
		auto *moduleData(m_private->modulerInstance->loadModule(fileName));
		if (moduleData) {
			IModule *loadedModule = reinterpret_cast<IModule*>(moduleData);
			return loadedModule;
		}
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
