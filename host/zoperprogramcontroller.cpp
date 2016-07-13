#include "zoperprogramcontroller.hpp"
#include "gamescene.hpp"
#include "common.hpp"

lib::uptr<lib::IApp> getModule() {
	return lib::uptr<lib::IApp>(new zoper::ZoperProgramController());
}

namespace zoper
{
	ZoperProgramController::ZoperProgramController()
	{
	}

	ZoperProgramController::~ZoperProgramController()
	{
//		saveConfig();
	}
		
	void ZoperProgramController::onInit()
	{
	}

	const lib::IAppDescriptor ZoperProgramController::getAppDescriptor() const
	{
		return lib::IAppDescriptor
		{
			"Zoper",
			1,
			1,
			1,
			"config.cfg",
			"res.cfg",
			lib::WindowCreationParams
			(
				std::string("ZOPER"),
				(lib::u32)1024,
				(lib::u32)768,
				(lib::u32)32,
				(lib::u32)0,
				false,
				false,
				false
				)
		};
	}

	int ZoperProgramController::loop()
	{
		return 0;
	}

	lib::VecSPtr<lib::draw::Scene> ZoperProgramController::scenesVector()
	{
		return{ /*lib::sptr<lib::draw::Scene>(new MenuScene),*/ lib::sptr<lib::draw::Scene>(new GameScene(appContext())) };
	}


}
