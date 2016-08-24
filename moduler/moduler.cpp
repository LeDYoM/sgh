#include "include/moduler.hpp"
#include <loader/include/loader.hpp>
#include <logger/include/logger.hpp>
#include <sstream>

namespace moduler
{
	static Moduler *modulerInstance{ nullptr };

	class ModulerPrivate
	{
	public:
		loader::Loader *loaderInstance{ nullptr };

		ModulerPrivate()
			: loaderInstance{ loader::createLoader() } {}

		~ModulerPrivate() { loader::destroyLoader(); }
	};

	Moduler::Moduler()
	{
		m_private = new ModulerPrivate;
	}

	Moduler::~Moduler()
	{
		delete m_private;
	}

	IModule *Moduler::loadModule(const char * fileName)
	{
		LOG_DEBUG_STR("Going to open " << fileName);
		auto *moduleData(m_private->loaderInstance->loadModule(fileName));
		if (moduleData) {
			IModule *loadedModule = reinterpret_cast<IModule*>(moduleData);
			return loadedModule;
		}
		return nullptr;
	}

	Moduler *createModuler ()
	{
		if (!modulerInstance) {
			LOG_DEBUG("Creating moduler...");
			modulerInstance = new Moduler;
			LOG_DEBUG("Moduler created");
		}
		else {
			LOG_DEBUG("Moduler already reated");
		}

		return modulerInstance;
	}

	void destroyModuler()
	{
		if (modulerInstance)
		{
			LOG_DEBUG("Destroying moduler...");
			delete modulerInstance;
			modulerInstance = nullptr;
			LOG_DEBUG("Moduler destroyed");
		}
	}
}
