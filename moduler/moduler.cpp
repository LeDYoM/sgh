#include "include/moduler.hpp"
#include "include/imoduleexport.hpp"
#include <loader/include/loader.hpp>
#include <logger/include/logger.hpp>
#include <sstream>
#include <list>

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

	struct ModuleHandle
	{
		using CreateModuleFunc = bool(*)();
		using GetModuleFunc = IModule * (*)();
		using DeleteModuleFunc = bool(*)();

		string fileName;
		uint_fast64_t system_uniqueId{};
		ModuleInformation *moduleInformation{ nullptr };
		CreateModuleFunc createModuleFunc{ nullptr };
		GetModuleFunc getModuleFunc{ nullptr };
		DeleteModuleFunc deleteModuleFunc{ nullptr };
		IModule *module{ nullptr };

		static bool sameModuleInformation(const ModuleInformation &lh, const ModuleInformation &rh) {
			return string(lh.name) == string(rh.name);

			// TO DO: Compare version numbers?
			// string(lh.version) == string(rh.version) &&
			// string(lh.subVersion) == string(rh.subVersion) &&
			// string(lh.patch) == string(rh.patch);
		}

		static bool sameModuleData(const ModuleHandle &lh, const ModuleHandle &rh) {
			return lh.system_uniqueId == rh.system_uniqueId && sameModuleInformation(*(lh.moduleInformation), *(rh.moduleInformation));

			// TO DO: Compare more data?
		}

	};

	using ModuleContainer = list<ModuleHandle>;

	class ModulerPrivate
	{
	public:
		loader::Loader *loaderInstance{ nullptr };
		ModuleContainer modules;

		ModulerPrivate() : loaderInstance{ loader::createLoader() } {}

		~ModulerPrivate()
		{
			loader::destroyLoader();
		}

		ModuleContainer::iterator pointerToIterator(const ModuleHandle* pointer_)
		{
			for (auto moduleHandleIterator = modules.begin(); moduleHandleIterator != modules.end(); ++moduleHandleIterator) {
				if (ModuleHandle::sameModuleData(*moduleHandleIterator, *pointer_)) {
					return moduleHandleIterator;
				}
			}
			return modules.end();
		}

		ModuleHandle* addModule(const ModuleHandle &moduleData)
		{
			modules.emplace_back(moduleData);
			return &(*prev(modules.end()));
		}

		bool deleteModule(const ModuleHandle *moduleHandle)
		{
			ASSERT_ERROR(moduleHandle, "Trying to delete nullptr moduleHandle");
			const ModuleHandle &moduleData = (*moduleHandle);
			LOG_DEBUG_STR("Going to delete module " << moduleData.fileName);
			moduleData.deleteModuleFunc();

			// Check that the deletion worked internally,
			// asking for the module pointer and checking for null
			ASSERT_WARNING(!moduleData.getModuleFunc(), "Deleter function does not delete the module");
			LOG_DEBUG_STR("Deleter worked: " << ((moduleData.getModuleFunc() == nullptr) ? "true" : "false"));
			return modules.erase(pointerToIterator(moduleHandle)) != modules.end();
		}

		ModuleContainer::iterator search(const ModuleHandle &moduleData)
		{
			auto it{ modules.begin() };
			while (it != modules.end()) {
				if (ModuleHandle::sameModuleData((*it), moduleData)) {
					return it;
				}
				++it;
			}
			return it;
		}

		void deleteAllModules()
		{
			while (modules.begin() != modules.end()) {
				string fileName((*modules.begin()).fileName);
				deleteModule(&*(modules.begin()));
				loaderInstance->unloadModule(fileName.c_str());
			}
		}
	};

	Moduler::Moduler()
	{
		m_private = new ModulerPrivate;
	}

	Moduler::~Moduler()
	{
		if (m_private) {
			m_private->deleteAllModules();
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
						ModuleHandle moduleData;
						moduleData.fileName = fileName;
						moduleData.moduleInformation = loadedModule->moduleInformation();
						moduleData.createModuleFunc = createModuleFunc;
						moduleData.getModuleFunc = getModuleFunc;
						moduleData.deleteModuleFunc = deleteModuleFunc;

						return m_private->addModule(moduleData);
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
