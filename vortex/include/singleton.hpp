#ifndef VTX_SINGLETON_INCLUDE_HPP
#define VTX_SINGLETON_INCLUDE_HPP

#include "comp_config.hpp"

namespace vtx
{
	template <class T>
	class Singleton
	{
	protected:
		Singleton() {}
		virtual ~Singleton() {}

	public:
		inline static T*const createInstance()
		{
			if (!instance_) {
				instance_ = new T{};
			}

			return instance_;
		}

		inline static T*const getInstance() { return instance_; }

		inline static void destroyInstance()
		{
			delete instance_;
			instance_ = nullptr;
		}

	private:
		static T* instance_;
	};

	template <class T> T*  Singleton<T>::instance_ = nullptr;
}

#endif
