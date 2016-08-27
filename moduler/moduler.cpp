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
				if (loadedModule) {
					auto *moduleInfo = loadedModule->moduleInformation();
					if (moduleInfo) {
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
						LOG_ERROR_STR("Error trying to get the module information");
						return nullptr;
					}
				}
				else {
					LOG_ERROR_STR("The method " << GET_MODULE_FUNC_NAME_STR << " returned nullptr");
					return nullptr;
				}
			}
			else {
				if (!createModuleFunc)
					LOG_ERROR_STR("Cannot read method " << CREATE_MODULE_FUNC_NAME_STR << "()");
				if (!getModuleFunc)
					LOG_ERROR_STR("Cannot read method " << GET_MODULE_FUNC_NAME_STR << "()");
				if (!deleteModuleFunc)
					LOG_ERROR_STR("Cannot read method "<< DELETE_MODULE_FUNC_NAME_STR << "()");

				// We are not going to use the loaded instance
				// TO DO: Delete object
//				m_private->loaderInstance->delete();
				return nullptr;
			}
		}
		return nullptr;
	}

	bool Moduler::unloadModule(const char *fileName)
	{
		auto iterator(m_private->modules.find(fileName));
		if (iterator != m_private->modules.end()) {

		}
		else {
			LOG_ERROR_STR("Module " << fileName << " not found to unload");
		}
	}

	Moduler *createModuler ()
	{

		if (!modulerInstance) {
			LOG_DEBUG("Creating moduler...");
			modulerInstance = new Moduler;
			LOG_DEBUG("Moduler created");
		}
		else {
			LOG_DEBUG("Moduler already created");
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
