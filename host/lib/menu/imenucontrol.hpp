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

			IMenuControl(const std::string &name) : lib::draw::RenderGroup(name) {}
			virtual ~IMenuControl() {}
			virtual void onKeyPressed(lib::input::Key key) = 0;
			virtual void onKeyReleased(lib::input::Key key) = 0;
			MenuManager * const menuManager() const
			{
				return dynamic_cast<MenuManager*const>(parent());
			}

			uptr<MenuTheme> const &menuTheme() const
			{
				return menuManager()->menuTheme();
			}
		};
	}
}

#endif
