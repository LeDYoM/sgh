#include "loadedInstance.hpp"

#ifdef _WIN32
#include <windows.h>
#endif

namespace moduler
{
	class LoadedInstancePrivate
	{
	public:
		LoadedInstancePrivate() {}
		~LoadedInstancePrivate() {}
#ifdef _WIN32
		HINSTANCE m_dllHandle;
#endif
	};

	LoadedInstance::LoadedInstance() : m_private{ new LoadedInstancePrivate }
	{

	}

	LoadedInstance::~LoadedInstance()
	{
		m_private.reset();
	}

	bool LoadedInstance::load(const char * fileName)
	{
#ifdef _WIN32
		m_private->m_dllHandle = LoadLibrary(fileName);
#endif
		return loaded();
	}

	void *LoadedInstance::loadMethod(const char *methodName)
	{
		if (loaded())
		{
			return static_cast<void*>(GetProcAddress(m_private->m_dllHandle,methodName));
		}
		return nullptr;
	}

	bool LoadedInstance::loaded() const
	{
		return m_private->m_dllHandle != nullptr;
	}

	bool LoadedInstance::unload()
	{
		if (loaded())
		{
#ifdef _WIN32
			FreeLibrary(m_private->m_dllHandle);
#endif
			m_private->m_dllHandle = nullptr;
			return true;
		}
		return false;
	}

}