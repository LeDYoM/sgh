#ifndef VTX_SINGLETON_INCLUDE_HPP
#define VTX_SINGLETON_INCLUDE_HPP

#include "comp_config.hpp"

namespace vtx
{
	template <class T>
	class Singleton
	{
	protected:
		constexpr Singleton() {}
		virtual ~Singleton() {}

		inline static T*const createInstance()
		{
			if (!instance_) {
				instance_ = new T{};
			}

			return instance_;
		}

		inline static void destroyInstance()
		{
			if (instance_) {
				delete instance_;
				instance_ = nullptr;
			}
		}

	public:
		inline static const T*const getConstInstance() noexcept { return instance_; }
		inline static T* getInstance() noexcept  { return instance_; }

	private:
		static T* instance_;
	};

	template <class T> T*  Singleton<T>::instance_ = nullptr;
}

#endif
