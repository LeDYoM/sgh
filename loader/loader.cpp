#include "include/loader.hpp"
#include "loadedinstance.hpp"
#include <map>

namespace loader
{
	class LoaderPrivate
	{
	public:
		LoaderPrivate() {}
		~LoaderPrivate() {}
		std::map<std::string, LoadedInstance*> m_loadedInstances;
	};

	static Loader *loaderInstance{ nullptr };

	Loader::Loader()
	{
		m_private = new LoaderPrivate;
	}

	Loader::~Loader()
	{
		delete m_private;
	}

	void *Loader::loadModule(const char *fileName)
	{
		LoadedInstance *loadedInstace = new LoadedInstance();
		loadedInstace->load(fileName);

		if (loadedInstace->loaded()) {
			m_private->m_loadedInstances[fileName] = loadedInstace;
		}
		return loadedInstace->loadedData();
	}

	void * Loader::loadMethod(const char *fileName, const char *methodName)
	{
		auto iterator(m_private->m_loadedInstances.find(fileName));
		if (iterator != m_private->m_loadedInstances.end()) {
			LoadedInstance* loadedInstance((*iterator).second);
			return loadedInstance->loadMethod(methodName);
		}
		return nullptr;
	}

	Loader * loader::createLoader()
	{
		if (!loaderInstance)
			loaderInstance = new Loader;

		return loaderInstance;
	}

	void destroyLoader()
	{
		if (loaderInstance)
		{
			delete loaderInstance;
			loaderInstance = nullptr;
		}
	}
}
