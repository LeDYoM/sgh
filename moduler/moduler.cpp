#include "include/moduler.hpp"
#include "include/imoduleexport.hpp"
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

	using CreateModuleFunc  = bool (*)();
	using GetModuleFunc = moduler::IModule * (*)();
	using DeleteModuleFunc = bool(*)();

	IModule *Moduler::loadModule(const char * fileName)
	{
		LOG_DEBUG_STR("Going to open " << fileName);
		auto *moduleData(m_private->loaderInstance->loadModule(fileName));
		if (moduleData) {
			LOG_DEBUG("Object file loaded");
			auto createModuleFunc = static_cast<CreateModuleFunc>(m_private->loaderInstance->loadMethod(fileName, CREATE_MODULE_FUNC_NAME_STR));
			auto getModuleFunc = static_cast<GetModuleFunc>(m_private->loaderInstance->loadMethod(fileName, GET_MODULE_FUNC_NAME_STR));
			auto deleteModuleFunc = static_cast<DeleteModuleFunc>(m_private->loaderInstance->loadMethod(fileName, DELETE_MODULE_FUNC_NAME_STR));
			if (createModuleFunc && getModuleFunc && deleteModuleFunc) {
				createModuleFunc();
				IModule *loadedModule = getModuleFunc();
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
