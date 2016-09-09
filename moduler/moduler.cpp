#include "include/moduler.hpp"
#include "modulerprivate.hpp"
#include "modulehandle.hpp"
#include "include/imoduleexport.hpp"
#include <loader/include/loader.hpp>
#include <logger/include/logger.hpp>
#include <sstream>

namespace moduler
{
	using namespace std;

	static Moduler *modulerInstance{ nullptr };

	inline string moduleSignature(const IModule*const module)
	{
		ostringstream t;
		t << module->moduleInformation()->name << " : " << module->moduleInformation()->version << "." << module->moduleInformation()->subVersion << module->moduleInformation()->patch;
		return t.str();
	}

	Moduler::Moduler()
	{
		m_private = new ModulerPrivate;
	}

	Moduler::~Moduler()
	{
		if (m_private) {
			delete m_private;
			m_private = nullptr;
		}
	}

	ModuleHandlePtr Moduler::loadModule(const char * fileName)
	{
		LOG_DEBUG_STR("Going to open " << fileName);
		auto *moduleObject(m_private->loaderInstance->loadModule(fileName));
		if (moduleObject) {
			LOG_DEBUG("Object file loaded");
			auto createModuleFunc = static_cast<ModuleHandle::CreateModuleFunc>(m_private->loaderInstance->loadMethod(fileName, CREATE_MODULE_FUNC_NAME_STR));
			auto getModuleFunc = static_cast<ModuleHandle::GetModuleFunc>(m_private->loaderInstance->loadMethod(fileName, GET_MODULE_FUNC_NAME_STR));
			auto deleteModuleFunc = static_cast<ModuleHandle::DeleteModuleFunc>(m_private->loaderInstance->loadMethod(fileName, DELETE_MODULE_FUNC_NAME_STR));
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
						ModuleHandle moduleHandle;
						moduleHandle.fileName = fileName;
						moduleHandle.createModuleFunc = createModuleFunc;
						moduleHandle.getModuleFunc = getModuleFunc;
						moduleHandle.deleteModuleFunc = deleteModuleFunc;

						return m_private->addModule(moduleHandle);
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
					LOG_ERROR_STR("Cannot read method " << DELETE_MODULE_FUNC_NAME_STR << "()");

				// We are not going to use the loaded instance
				// TO DO: Delete object
//				m_private->loaderInstance->delete();
				return nullptr;
			}
		}
		return nullptr;
	}

	bool Moduler::unloadModule(ModuleHandlePtr&&moduleHandlePtr)
	{
		ASSERT_ERROR(moduleHandlePtr, "unloadModule: called with nullptr");
		const ModuleHandle &moduleData(*moduleHandlePtr);
		LOG_DEBUG_STR("Trying to unload module " << moduleSignature(moduleData.module));
		// Store the string file name before removing the module from the modules list. We need it to remove the module from the loader.
		const string fileName(moduleData.fileName);
		bool result(m_private->deleteModule(moduleHandlePtr));
		return m_private->loaderInstance->unloadModule(fileName.c_str()) ? result : false;
	}

	ModuleHandlePtr Moduler::addDirectModule(IModule *module)
	{
		ModuleHandle moduleHandle;
		moduleHandle.createModuleFunc = nullptr;
		moduleHandle.deleteModuleFunc = nullptr;
		moduleHandle.getModuleFunc = nullptr;
		moduleHandle.module = module;
		moduleHandle.fileName = "";

		return m_private->addModule(std::move(moduleHandle));
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
