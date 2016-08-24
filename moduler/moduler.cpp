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

	typedef moduler::IModule * (*createModuleFunc)();
	typedef void (*deleteModuleFunc)(moduler::IModule *);

	IModule *Moduler::loadModule(const char * fileName)
	{
		LOG_DEBUG_STR("Going to open " << fileName);
		auto *moduleData(m_private->loaderInstance->loadModule(fileName));
		if (moduleData) {
			LOG_DEBUG("Object file loaded");
			auto creatorFunc = static_cast<createModuleFunc>(m_private->loaderInstance->loadMethod(fileName, "createModule"));
			auto deleterFunc = static_cast<deleteModuleFunc>(m_private->loaderInstance->loadMethod(fileName, "deleteModule"));
			if (creatorFunc && deleterFunc) {
				IModule *loadedModule = creatorFunc();
				return loadedModule;
			}
			else {
				LOG_WARNING("Cannot read method createModule()");
			}
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
