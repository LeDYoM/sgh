#include "modulerprivate.hpp"
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

	ModulerPrivate::ModulerPrivate() : loaderInstance{ loader::createLoader() } {}

	ModulerPrivate::~ModulerPrivate()
	{
		deleteAllModules();
		loader::destroyLoader();
	}

	ModuleContainer::iterator ModulerPrivate::pointerToIterator(const ModuleHandle* pointer_)
	{
		for (auto moduleHandleIterator = modules.begin(); moduleHandleIterator != modules.end(); ++moduleHandleIterator) {
			if (*moduleHandleIterator == *pointer_) {
				return moduleHandleIterator;
			}
		}
		return modules.end();
	}

	ModuleHandle* ModulerPrivate::addModule(const ModuleHandle &moduleHandle)
	{
		modules.emplace_back(moduleHandle);
		return &(*prev(modules.end()));
	}

	bool ModulerPrivate::deleteModule(const ModuleHandle *moduleHandlePtr)
	{
		ASSERT_ERROR(moduleHandlePtr, "Trying to delete nullptr moduleHandle");
		const ModuleHandle &moduleData = (*moduleHandlePtr);
		LOG_DEBUG_STR("Going to delete module " << moduleData.fileName);
		moduleData.deleteModuleFunc();

		// Check that the deletion worked internally,
		// asking for the module pointer and checking for null
		ASSERT_WARNING(!moduleData.getModuleFunc(), "Deleter function does not delete the module");
		LOG_DEBUG_STR("Deleter worked: " << ((moduleData.getModuleFunc() == nullptr) ? "true" : "false"));
		return modules.erase(pointerToIterator(moduleHandlePtr)) != modules.end();
	}

	void ModulerPrivate::incrementModuleReferenceCounter(ModuleHandle *const moduleHandle)
	{
		ASSERT_CRITICAL(moduleHandle, "Passed nullptr pointer");
		++(moduleHandle->referenceConunter);
	}

	ModuleContainer::iterator ModulerPrivate::search(const ModuleHandle &moduleData)
	{
		auto it{ modules.begin() };
		while (it != modules.end()) {
			if (*it == moduleData) {
				return it;
			}
			++it;
		}
		return it;
	}

	void ModulerPrivate::deleteAllModules()
	{
		while (modules.begin() != modules.end()) {
			string fileName((*modules.begin()).fileName);
			deleteModule(&*(modules.begin()));
			loaderInstance->unloadModule(fileName.c_str());
		}
	}
}
