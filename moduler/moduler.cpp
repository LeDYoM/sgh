#include "include/moduler.hpp"
#include "include/imoduleexport.hpp"
#include <loader/include/loader.hpp>
#include <logger/include/logger.hpp>
#include <sstream>
#include <map>

namespace moduler
{
	static Moduler *modulerInstance{ nullptr };

	struct ModuleData
	{
		using CreateModuleFunc = bool(*)();
		using GetModuleFunc = moduler::IModule * (*)();
		using DeleteModuleFunc = bool(*)();

		ModuleInformation *moduleInformation{ nullptr };
		CreateModuleFunc createModuleFunc{ nullptr };
		GetModuleFunc getModuleFunc{ nullptr };
		DeleteModuleFunc deleteModuleFunc{ nullptr };

		std::string fileName;
	};
	class ModulerPrivate
	{
	public:
		loader::Loader *loaderInstance{ nullptr };
		std::map<std::string, ModuleData> modules;
		ModulerPrivate()
			: loaderInstance{ loader::createLoader() } 
		{}

		~ModulerPrivate()
		{
			loader::destroyLoader(); 
		}
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
		auto *moduleObject(m_private->loaderInstance->loadModule(fileName));
		if (moduleObject) {
			LOG_DEBUG("Object file loaded");
			auto createModuleFunc = static_cast<ModuleData::CreateModuleFunc>(m_private->loaderInstance->loadMethod(fileName, CREATE_MODULE_FUNC_NAME_STR));
			auto getModuleFunc = static_cast<ModuleData::GetModuleFunc>(m_private->loaderInstance->loadMethod(fileName, GET_MODULE_FUNC_NAME_STR));
			auto deleteModuleFunc = static_cast<ModuleData::DeleteModuleFunc>(m_private->loaderInstance->loadMethod(fileName, DELETE_MODULE_FUNC_NAME_STR));
			if (createModuleFunc && getModuleFunc && deleteModuleFunc) {
				LOG_INFO_STR("Module from " << fileName << " has correct interface definition");
				LOG_INFO("Initializing module...");
				createModuleFunc();
				IModule *loadedModule = getModuleFunc();
				auto *moduleInfo = loadedModule->moduleInformation();
				LOG_INFO("Module info:");
				LOG_INFO_STR("Name: " << moduleInfo->name);
				LOG_INFO_STR("Version: " << moduleInfo->version << "." << moduleInfo->subVersion << "." << moduleInfo->patch);
				LOG_INFO("Seems module has correct implementation");
				ModuleData moduleData;
				moduleData.moduleInformation = loadedModule->moduleInformation();
				moduleData.createModuleFunc = createModuleFunc;
				moduleData.getModuleFunc = getModuleFunc;
				moduleData.deleteModuleFunc = deleteModuleFunc;

				m_private->modules[fileName] = moduleData;
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
