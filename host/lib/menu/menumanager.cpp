#include "menumanager.hpp"
#include "menustep.hpp"
#include <lib/core/log.hpp>
#include "menutheme.hpp"

namespace lib
{
	namespace menu
	{
		MenuManager::MenuManager(const std::string &name)
			: Scene{ name }
		{
//			_steps = stepsVector();
//			getSteps();
		}

		bool MenuManager::init()
		{
			using namespace draw;
			if (Scene::init())
			{
				m_mTheme = uptr<MenuTheme>(new MenuTheme{ Color{ 0, 0, 255 }, Color{ 255, 0, 0 }, "game_menu.mainFont" });
//				m_mTheme->notSelectedColor.s
				return true;
			}
			return false;
		}

		MenuManager::~MenuManager()
		{
		}

		void MenuManager::addMenuStep(sptr<MenuStep> step)
		{
			addRenderGroup(step);
		}

		void MenuManager::start(sptr<MenuStep> firstStep)
		{
			__ASSERT(firstStep, "Cannot start in nullptr step");
			changeStep(firstStep);
		}

		void MenuManager::start(const std::string &firstStep)
		{
			changeStep(firstStep);
		}

		void MenuManager::changeStep(const std::string &step)
		{
			setActiveStep(findByNameAs<MenuStep>(step));
		}

		void MenuManager::changeStep(sptr<MenuStep> step)
		{
			setActiveStep(step);
		}

		void MenuManager::setActiveStep(sptr<MenuStep> step)
		{
			activateOne(step);
		}

		void MenuManager::onKeyPressed(lib::input::Key key)
		{
			_activeMenuStep->onKeyPressed(key);
		}

		void MenuManager::onKeyReleased(lib::input::Key key)
		{
			_activeMenuStep->onKeyReleased(key);
		}
	}
}
