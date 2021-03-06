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
		uint_fast16_t referenceConunter{};
		inline const ModuleInformation * moduleInformation() const { return module->moduleInformation(); }
		CreateModuleFunc createModuleFunc{ nullptr };
		GetModuleFunc getModuleFunc{ nullptr };
		DeleteModuleFunc deleteModuleFunc{ nullptr };
		IModule *module{ nullptr };

		inline std::string moduleName() const { return moduleInformation()->name; }

		bool sameModuleInformation(const ModuleHandle &rh) const {
			return std::string(moduleName()) == std::string(rh.moduleName());

			// TO DO: Compare version numbers?
			// string(lh.version) == string(rh.version) &&
			// string(lh.subVersion) == string(rh.subVersion) &&
			// string(lh.patch) == string(rh.patch);
		}

		bool operator==(const ModuleHandle &rh) const {
			return system_uniqueId == rh.system_uniqueId && sameModuleInformation(rh);

			// TO DO: Compare more data?
		}

		bool operator!=(const ModuleHandle &rh) const {
			return system_uniqueId != rh.system_uniqueId || !sameModuleInformation(rh);

			// TO DO: Compare more data?
		}
	};
}

#endif
