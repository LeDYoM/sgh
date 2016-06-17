#ifndef __MAINMENU_HPP__
#define __MAINMENU_HPP__

#include <lib/menu/menustep.hpp>
#include <lib/menu/simplemenu.hpp>
#include <lib/core/configuration.hpp>

namespace zoper
{
	namespace zmenu
	{
		class MainMenu : public lib::menu::MenuStep
		{
		public:
			MainMenu(lib::draw::RenderGroup *const p_parent);
			virtual ~MainMenu();

			virtual bool init() override;

		private:
			lib::Configuration _gameConfig;
			lib::sptr<lib::menu::SimpleMenu> _chooseControl{ nullptr };
		};
	}
}

#endif
