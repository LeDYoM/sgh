#ifndef VTX_VORTEX_APPLICATION_INTERNAL_HPP
#define VTX_VORTEX_APPLICATION_INTERNAL_HPP

#include "comp_config.hpp"
#include "common_def.hpp"
#include "singleton.hpp"

namespace vtx
{
	class VApplication;

	class VORTEX_API Vortex final : public Singleton<Vortex>
	{
	public:
		inline static Vortex*const createInstance() { return Singleton<Vortex>::createInstance(); }
		inline static void destroyInstance() { return Singleton<Vortex>::destroyInstance(); }

		void setCommandLineParameters(int argc, char* argv[]);
		bool setApplication(VApplication*);
		void initialize();
		void deinitialize();

		int execute();
	protected:
		Vortex();
		~Vortex();

		friend class Singleton<Vortex>;
		DECLARE_PRIVATE_MPRIVATE_PIMPL(Vortex)
	};

	bool VORTEX_API Vortex_Init();
	int VORTEX_API Vortex_Loop();
	bool VORTEX_API Vortex_DeInit();

}

#endif
