#ifndef __LIB_MENUSTEP_HPP__
#define __LIB_MENUSTEP_HPP__

#include <lib/draw/rendergroup.hpp>
#include <lib/menu/imenucontrol.hpp>
#include <lib/include/types.hpp>
#include <lib/include/key.hpp>

#include <vector>
#include <memory>

namespace lib
{
	namespace menu
	{
		class MenuManager;
		class MenuStep : public draw::RenderGroup
		{
		public:
			MenuStep(RenderGroup *const p_parent, const std::string &name);
			virtual ~MenuStep();

			MenuManager *menuManager();

			void addMenuControl(sptr<IMenuControl> nControl);
			virtual void onKeyPressed(lib::Key kEvent);
			virtual void onKeyReleased(lib::Key kEvent);
		};
	}
}

#endif
