#ifndef __STARTLEVELMENU_HPP__
#define __STARTLEVELMENU_HPP__

#include <lib/menu/menustep.hpp>
#include <lib/menu/choosecontrol.hpp>
#include <lib/core/configuration.hpp>

namespace zoper
{
	namespace zmenu
	{
		class StartLevelMenu : public lib::menu::MenuStep, public lib::Configuration
		{
		public:
			StartLevelMenu(lib::draw::RenderGroup *const p_parent);
			virtual ~StartLevelMenu();
			virtual bool init() override;

		private:
			lib::Configuration _gameConfig;
			lib::sptr<lib::menu::ChooseControl> _chooseControl{ nullptr };
		};
	}
}

#endif
