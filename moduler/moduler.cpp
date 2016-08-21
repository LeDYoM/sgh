#include "include/moduler.hpp"
#include "loadedinstance.hpp"
#include <map>

namespace moduler
{
	class ModulerPrivate
	{
	public:
		ModulerPrivate() {}
		~ModulerPrivate() {}
		std::map<std::string, LoadedInstance*> m_loadedInstances;
	};

	static Moduler *modulerInstance{ nullptr };

	Moduler::Moduler()
	{
		m_private = new ModulerPrivate;
	}

	Moduler::~Moduler()
	{
		delete m_private;
	}

	bool Moduler::loadModule(const char *fileName)
	{
		LoadedInstance *loadedInstace = new LoadedInstance();
		loadedInstace->load(fileName);

		if (loadedInstace->loaded()) {
			m_private->m_loadedInstances[fileName] = loadedInstace;
		}
		return loadedInstace->loaded();
	}

	void * Moduler::loadMethod(const char *fileName, const char *methodName)
	{
		auto iterator(m_private->m_loadedInstances.find(fileName));
		if (iterator != m_private->m_loadedInstances.end()) {
			LoadedInstance* loadedInstance((*iterator).second);
			return loadedInstance->loadMethod(methodName);
		}
		return nullptr;
	}

	Moduler * moduler::createModuler()
	{
		if (!modulerInstance)
			modulerInstance = new Moduler;

		return modulerInstance;
	}

	void destroyModuler()
	{
		if (modulerInstance)
		{
			delete modulerInstance;
			modulerInstance = nullptr;
		}
	}

}
