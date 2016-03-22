#include "mainmenu.hpp"
#include <lib/menu/menumanager.hpp>
#include <lib/menu/choosecontrol.hpp>
#include <lib/menu/menudescriptors.hpp>
#include <lib/draw/rendernode.hpp>
#include <lib/core/resourcemanager.hpp>
#include <lib/core/resource.hpp>
#include <lib/menu/simplemenu.hpp>
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

		bool MainMenu::init()
		{
			if (MenuStep::init())
			{
				auto callBack = [this](lib::u32 index, lib::menu::SimpleMenu &self)
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
				_chooseControl = lib::sptr<lib::menu::SimpleMenu>(new lib::menu::SimpleMenu("mainmenu_chooseControl",
					//				menuManager()->resourceManager()->getResource("game_menu.mainFont"),
					//				lib::draw::Color::Blue(), lib::draw::Color::Red(),
					lib::draw::NodeText::Alignment::Center,
					//				90, 1,
					callBack
					/*
					lib::sptr<lib::menu::CursorDescriptor>(new lib::menu::CursorDescriptor(3, lib::vector2df{ 90.0f, 90.0f },lib::draw::Color::Red())),
					std::vector<lib::sptr<lib::menu::OptionDescriptor>>{
					lib::sptr<lib::menu::OptionDescriptor>(new lib::menu::OptionDescriptor("Play token mode")),
					lib::sptr<lib::menu::OptionDescriptor>(new lib::menu::OptionDescriptor("Play time mode")),
					lib::sptr<lib::menu::OptionDescriptor>(new lib::menu::OptionDescriptor("Options")),
					lib::sptr<lib::menu::OptionDescriptor>(new lib::menu::OptionDescriptor("Exit"))
					*/
					));
				addMenuControl(_chooseControl);
				_chooseControl->addOption("Play token mode");
				_chooseControl->addOption("Play time mode");
				_chooseControl->addOption("Options");
				_chooseControl->addOption("Exit");
				//			_chooseControl->setPosition({ menuManager()->camera().target().center().x, 700 });
				return true;
			}
			return false;
		}
	}
}
