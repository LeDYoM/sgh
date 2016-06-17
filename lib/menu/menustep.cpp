#include "menustep.hpp"
#include "menumanager.hpp"

namespace lib
{
	namespace menu
	{
		MenuStep::MenuStep(RenderGroup *const p_parent, const std::string &name)
			: RenderGroup(p_parent, name)
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
			addNode(nControl);
		}

		void MenuStep::onKeyPressed(lib::Key key)
		{
			key;
//			for (auto control : _renderNodes)
//			{
//				control->onKeyPressed(key);
//			}
		}

		void MenuStep::onKeyReleased(lib::Key key)
		{
			key;
//			for (auto control : _controls)
//			{
//				control->onKeyReleased(key);
//			}
		}

	}
}
