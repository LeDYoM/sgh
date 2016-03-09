#include "menumanager.hpp"
#include "menustep.hpp"
#include <lib/core/log.hpp>

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


		MenuManager::~MenuManager()
		{
			_steps.clear();
		}

		void MenuManager::addMenuSteps(std::vector<sptr<MenuStep>> &steps)
		{
			for (auto menuStep : steps)
			{
				addMenuStep(menuStep);
			}
		}

		void MenuManager::addMenuStep(sptr<MenuStep> step)
		{
			addRenderGroup(step);
			_steps.push_back(step);
			step->onCreate();
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
			for (const auto nstep : _steps)
			{
				if (nstep->name() == step)
				{
					changeStep(nstep);
				}
			}
		}

		void MenuManager::changeStep(sptr<MenuStep> step)
		{
			setActiveStep(step);
		}

		void MenuManager::setActiveStep(sptr<MenuStep> step)
		{
			_activeMenuStep = step;

			for (auto _step : _steps)
			{
				_step->setVisible(_step == step);
			}
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
