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
		}

		void MenuStep::onKeyPressed(lib::Key key)
		{
//			for (auto control : _renderNodes)
//			{
//				control->onKeyPressed(key);
//			}
		}

		void MenuStep::onKeyReleased(lib::Key key)
		{
//			for (auto control : _controls)
//			{
//				control->onKeyReleased(key);
//			}
		}

	}
}
