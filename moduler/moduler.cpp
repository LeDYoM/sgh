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

	struct ModuleData
	{
		using CreateModuleFunc = bool(*)();
		using GetModuleFunc = moduler::IModule * (*)();
		using DeleteModuleFunc = bool(*)();

		string fileName;
		uint_fast64_t system_uniqueId{};
		ModuleInformation *moduleInformation{ nullptr };
		CreateModuleFunc createModuleFunc{ nullptr };
		GetModuleFunc getModuleFunc{ nullptr };
		DeleteModuleFunc deleteModuleFunc{ nullptr };

		static bool sameModuleInformation(const ModuleInformation &lh, const ModuleInformation &rh) {
			return string(lh.name) == string(rh.name);

			// TO DO: Compare version numbers?
			// string(lh.version) == string(rh.version) &&
			// string(lh.subVersion) == string(rh.subVersion) &&
			// string(lh.patch) == string(rh.patch);
		}

		static bool sameModuleData(const ModuleData &lh, const ModuleData &rh) {
			return lh.system_uniqueId == rh.system_uniqueId && sameModuleInformation(*(lh.moduleInformation), *(rh.moduleInformation));

			// TO DO: Compare more data?
		}
	};

	class ModulerPrivate
	{
	public:
		using ModuleContainer = list<ModuleData>;

		loader::Loader *loaderInstance{ nullptr };
		ModuleContainer modules;

		ModulerPrivate() : loaderInstance{ loader::createLoader() } {}

		~ModulerPrivate()
		{
			loader::destroyLoader();
		}

		void addModule(ModuleData &&moduleData)
		{
			modules.emplace_back(move(moduleData));
		}

		bool deleteModule(const ModuleContainer::iterator &it)
		{
			const ModuleData &moduleData = *it;
			LOG_DEBUG_STR("Going to delete module " << moduleData.fileName);
			moduleData.deleteModuleFunc();

			// Check that the deletion worked internally,
			// asking for the module pointer and checking for null
			ASSERT_WARNING(!moduleData.getModuleFunc(), "Deleter function does not delete the module");
			LOG_DEBUG_STR("Deleter worked: " << ((moduleData.getModuleFunc() == nullptr) ? "true" : "false"));
			return modules.erase(it) != modules.end();
		}

		ModuleContainer::iterator search(const ModuleData &moduleData)
		{
			auto it{ modules.begin() };
			while (it != modules.end()) {
				if (ModuleData::sameModuleData((*it), moduleData)) {
					return it;
				}
				++it;
			}
			return it;
		}

		ModuleContainer::iterator searchDataFromInfo(const ModuleInformation &moduleInformation)
		{
			auto it(modules.begin());
			while (it != modules.end()) {
				if (ModuleData::sameModuleInformation((*(*it).moduleInformation), moduleInformation)) {
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
				deleteModule(modules.begin());
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
						moduleData.fileName = fileName;
						moduleData.moduleInformation = loadedModule->moduleInformation();
						moduleData.createModuleFunc = createModuleFunc;
						moduleData.getModuleFunc = getModuleFunc;
						moduleData.deleteModuleFunc = deleteModuleFunc;

						m_private->addModule(move(moduleData));
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
					LOG_ERROR_STR("Cannot read method " << DELETE_MODULE_FUNC_NAME_STR << "()");

				// We are not going to use the loaded instance
				// TO DO: Delete object
//				m_private->loaderInstance->delete();
				return nullptr;
			}
		}
		return nullptr;
	}

	bool Moduler::unloadModule(IModule*module)
	{
		ASSERT_ERROR(module, "Module parameter cannot be nullptr");
		LOG_DEBUG_STR("Trying to unload module " << moduleSignature(module));
		const auto moduleData( m_private->searchDataFromInfo(*(module->moduleInformation())) );
		ASSERT_ERROR_STR(moduleData != m_private->modules.end(), "Internal data error: Module internal data for module "<< moduleSignature(module));
		if (moduleData != m_private->modules.end()) {
			m_private->deleteModule(moduleData);
			// Store the string file name before removing the module from the modules list. We need it to remove the module from the loader.
			const string fileName(moduleData->fileName);
			bool result(m_private->deleteModule(moduleData));
			return m_private->loaderInstance->unloadModule(fileName.c_str()) ? result : false;
		}
		else {
			LOG_ERROR_STR("Module " << moduleSignature(module) << " not found to unload");
		}
		return false;
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
