#include "menuscene.hpp"
#include <lib/draw/nodeshape.hpp>
#include <lib/draw/nodetext.hpp>
#include <lib/core/resourcemanager.hpp>
#include <lib/core/resource.hpp>

#include "mainmenu.hpp"
#include "optionsmenu.hpp"
#include "keyredefinitionmenu.hpp"
#include "startlevelmenu.hpp"

namespace zoper
{
	MenuScene::MenuScene(lib::draw::SceneManager *const pSceneManager)
		: lib::menu::MenuManager(pSceneManager, "MenuScene"), m_keyMapping{ this } {}

	MenuScene::~MenuScene() {}

	bool MenuScene::init()
	{
		if (MenuManager::init())
		{
			_background = createSpriteShape("background");

			addMenuStep(lib::sptr<lib::menu::MenuStep>(new zoper::zmenu::MainMenu(this)));
			addMenuStep(lib::sptr<lib::menu::MenuStep>(new zoper::zmenu::OptionsMenu(this)));
			addMenuStep(lib::sptr<lib::menu::MenuStep>(new zoper::zmenu::KeyRedefinitionMenu(this)));
			addMenuStep(lib::sptr<lib::menu::MenuStep>(new zoper::zmenu::StartLevelMenu(this)));

			_logo = createSpriteShape("mainLogo");
			_logo->setTexture(resourceManager()->getResource("game_menu.logo")->getAsTexture(), true, false);
			_logo->setSize(lib::vector2df(800, 400));
//			_logo->setPositionX(camera().target().center().x, lib::draw::Alignment::Center);
//			_logo->setPositionY(100);

			_background->setTexture(resourceManager()->getResource("game_menu.background")->getAsTexture(), true, false);
			_background->setSize(2000.0f);
			return true;
		}
		return false;
	}

	bool MenuScene::deinit()
	{
		return Scene::deinit();
	}

	void MenuScene::onEnterScene()
	{
		start("MainMenu");
	}

	void MenuScene::onExitScene()
	{
	}

	void MenuScene::update()
	{

	}

	const lib::vector2df MenuScene::getDefaultSizeView()
	{
		return{ 2000.0f, 2000.0f };
	}
}
