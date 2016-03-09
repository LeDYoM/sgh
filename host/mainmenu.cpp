#include "mainmenu.hpp"
#include <lib/menu/menumanager.hpp>
#include <lib/menu/choosecontrol.hpp>
#include <lib/menu/menudescriptors.hpp>
#include <lib/draw/RenderNode.hpp>
#include <lib/core/resourcemanager.hpp>
#include <lib/core/resource.hpp>

#include "common.hpp"

namespace zoper
{
	namespace zmenu
	{
		MainMenu::MainMenu()
			: lib::menu::MenuStep{ "MainMenu" }, _gameConfig{ ":NextGame" }
		{
		}


		MainMenu::~MainMenu()
		{
		}

		void MainMenu::onCreate()
		{
			auto callBack = [this](lib::u32 index, lib::menu::ChooseControl &self)
			{
				self;
				switch (index)
				{
				case 0:
					_gameConfig.addConfigInt(GameModeStr, 0, true);
					menuManager()->changeStep("StartLevelMenu");
					break;
				case 1:
					_gameConfig.addConfigInt(GameModeStr, 1, true);
					menuManager()->changeStep("StartLevelMenu");
					break;
				case 2:
					menuManager()->changeStep("OptionsMenu");
					break;
				case 3:
				default:
					menuManager()->exitProgram();
					break;
				}
			};
			_chooseControl = lib::sptr<lib::menu::ChooseControl>(new lib::menu::ChooseControl("mainmenu_chooseControl",
				menuManager()->sceneHandle->resourceManager()->getResource("game_menu.mainFont"),
				lib::draw::Color::Blue(), lib::draw::Color::Red(),
				lib::draw::Alignment::Center,
				90, 1,
				callBack,
				lib::sptr<lib::menu::CursorDescriptor>(new lib::menu::CursorDescriptor(3, lib::vector2df{ 90.0f, 90.0f },lib::draw::Color::Red())),
				std::vector<lib::sptr<lib::menu::OptionDescriptor>>{
				lib::sptr<lib::menu::OptionDescriptor>(new lib::menu::OptionDescriptor("Play token mode")),
					lib::sptr<lib::menu::OptionDescriptor>(new lib::menu::OptionDescriptor("Play time mode")),
				lib::sptr<lib::menu::OptionDescriptor>(new lib::menu::OptionDescriptor("Options")),
				lib::sptr<lib::menu::OptionDescriptor>(new lib::menu::OptionDescriptor("Exit"))
			}));
			addMenuControl(_chooseControl);
			_chooseControl->setPosition({ menuManager()->sceneHandle->camera().target().center().x, 700 });
		}
	}
}
