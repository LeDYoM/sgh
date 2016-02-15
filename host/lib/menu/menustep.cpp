#include "menustep.hpp"
#include "menumanager.hpp"

namespace lib
{
	namespace menu
	{
		MenuStep::MenuStep(const std::string &name)
			: RenderGroup(name)
		{
		}


		MenuStep::~MenuStep()
		{
		}

		MenuManager * MenuStep::menuManager()
		{
			return dynamic_cast<MenuManager*>(parent());
		}

		void MenuStep::addMenuControl(sptr<IMenuControl> nControl)
		{
			addRenderGroup(nControl);
			_controls.push_back(nControl);
		}

		void MenuStep::onKeyPressed(lib::input::Key key)
		{
			for (auto control : _controls)
			{
				control->onKeyPressed(key);
			}
		}

		void MenuStep::onKeyReleased(lib::input::Key key)
		{
			for (auto control : _controls)
			{
				control->onKeyReleased(key);
			}
		}

	}
}
