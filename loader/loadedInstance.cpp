#include "loadedinstance.hpp"
#include <map>
#include <string>

#if defined(_MSC_VER) || defined(__BORLANDC__)
	#define WIN32_LEAN_AND_MEAN
	#include <windows.h>
	inline void *getMethod(void *handle, const char *methodName)
	{
		return static_cast<void*>(GetProcAddress(static_cast<HMODULE>(handle), methodName));
	}

	inline void *loadSharedObject(const char *fileName)
	{
		return static_cast<void*>(LoadLibrary(fileName));
	}
#endif

namespace loader
{
	using namespace std;

	class LoadedInstancePrivate
	{
	public:
		LoadedInstancePrivate() {}
		~LoadedInstancePrivate() 
		{
			m_methods.clear();
		}

		void *m_sharedFileHandle;
		map<string, void*> m_methods;
	};

	LoadedInstance::LoadedInstance() : m_private{ new LoadedInstancePrivate } {}

	LoadedInstance::~LoadedInstance()
	{
		m_private.reset();
	}

	bool LoadedInstance::load(const char * fileName)
	{
		m_private->m_sharedFileHandle = loadSharedObject(fileName);
		return loaded();
	}

	void *LoadedInstance::loadMethod(const char *methodName)
	{
		if (loaded()) {
			auto node(m_private->m_methods.find(methodName));
			if (node == m_private->m_methods.end()) {
				auto methodAddress(getMethod(m_private->m_sharedFileHandle, methodName));

				// Add the result of getMethod even if is nullptr to avoid
				// trying to load it more times
				m_private->m_methods[methodName] = methodAddress;
				return methodAddress;
			}
			else {
				// The method is already on the map, return it
				return node->second;
			}
		}
		return nullptr;
	}

	bool LoadedInstance::loaded() const
	{
		return m_private->m_sharedFileHandle != nullptr;
	}

	bool LoadedInstance::unload()
	{
		if (loaded())
		{
#ifdef _WIN32
			FreeLibrary(static_cast<HMODULE>(m_private->m_sharedFileHandle));
#endif
			m_private->m_sharedFileHandle = nullptr;
			return true;
		}
		return false;
	}

	void * LoadedInstance::loadedData() const
	{
		return m_private->m_sharedFileHandle;
	}

}
