#ifndef MODULER_LOADEDINSTANCE_HPP
#define MODULER_LOADEDINSTANCE_HPP

#include <memory>

namespace moduler
{
	class LoadedInstancePrivate;

	class LoadedInstance
	{
	public:
		LoadedInstance();
		~LoadedInstance();

		bool load(const char *fileName);
		void *loadMethod(const char *methodName);

		bool loaded() const;
		bool unload();
		void *loadedData() const;
	private:
		std::unique_ptr<LoadedInstancePrivate> m_private;
	};
}
#endif