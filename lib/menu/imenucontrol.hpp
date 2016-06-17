#ifndef __LIB_IMENUCONTROL_HPP__
#define __LIB_IMENUCONTROL_HPP__

#include <lib/draw/rendergroup.hpp>
#include <lib/include/key.hpp>
#include <lib/include/color.hpp>
#include "menumanager.hpp"
#include <lib/draw/scene.hpp>

namespace lib
{
	namespace menu
	{
		class IMenuControl : public lib::draw::RenderGroup
		{
		public:

			IMenuControl(RenderGroup *const p_parent, const std::string &name) : lib::draw::RenderGroup(p_parent, name) {}
			virtual ~IMenuControl() {}
			virtual void onKeyPressed(lib::Key key) = 0;
			virtual void onKeyReleased(lib::Key key) = 0;
			MenuManager * const menuManager()
			{
				return dynamic_cast<MenuManager *const>(parentScene());
			}

			sptr<MenuTheme> const &menuTheme()
			{
				return menuManager()->menuTheme();
			}
		};
	}
}

#endif
