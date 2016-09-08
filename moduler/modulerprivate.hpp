#ifndef MODULER_MODULERPRIVATE_HPP
#define MODULER_MODULERPRIVATE_HPP

#include "include/moduler.hpp"
#include "modulehandle.hpp"
#include <list>

namespace loader
{
	class Loader;
}

namespace moduler
{
	using ModuleContainer = std::list<ModuleHandle>;

	class ModulerPrivate
	{
	public:
		loader::Loader *loaderInstance{ nullptr };

		ModulerPrivate();
		~ModulerPrivate();
		ModuleContainer::iterator pointerToIterator(const ModuleHandle* pointer_);
		ModuleHandle* addModule(const ModuleHandle &moduleData);
		bool deleteModule(const ModuleHandle *moduleHandle);

		ModuleContainer::iterator search(const ModuleHandle &moduleData);
		void deleteAllModules();
	private:
		ModuleContainer modules;
	};
}

#endif
