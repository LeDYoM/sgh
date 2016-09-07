#ifndef MODULER_MODULEHANDLE_HPP
#define MODULER_MODULEHANDLE_HPP

#include "include/moduler.hpp"
#include <string>

namespace moduler
{
	struct ModuleHandle
	{
		using CreateModuleFunc = bool(*)();
		using GetModuleFunc = IModule * (*)();
		using DeleteModuleFunc = bool(*)();

		std::string fileName;
		uint_fast64_t system_uniqueId{};
		ModuleInformation *moduleInformation{ nullptr };
		CreateModuleFunc createModuleFunc{ nullptr };
		GetModuleFunc getModuleFunc{ nullptr };
		DeleteModuleFunc deleteModuleFunc{ nullptr };
		IModule *module{ nullptr };

		inline std::string moduleName() const { return moduleInformation->name; }

		static bool sameModuleInformation(const ModuleInformation &lh, const ModuleInformation &rh) {
			return std::string(lh.name) == std::string(rh.name);

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
}

#endif
