#include "zoperprogramcontroller.hpp"
#include "gamescene.hpp"
#include "common.hpp"

using namespace lib;

uptr<IApp> getModule() {
	return uptr<IApp>(new zoper::ZoperProgramController());
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

	const IAppDescriptor ZoperProgramController::getAppDescriptor() const
	{
		return IAppDescriptor
		{
			"Zoper",
			1,
			1,
			1,
			"config.cfg",
			"res.cfg",
		};
	}

	int ZoperProgramController::loop()
	{
		return 0;
	}

	VecSPtr<draw::Scene> ZoperProgramController::scenesVector()
	{
		return{ /*sptr<draw::Scene>(new MenuScene),*/ sptr<draw::Scene>(new GameScene(appContext())) };
	}


}
