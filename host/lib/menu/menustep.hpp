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
			MenuStep(const std::string &name);
			virtual ~MenuStep();

			virtual void onCreate() = 0;
			MenuManager *menuManager();

			void addMenuControl(sptr<IMenuControl> nControl);
			virtual void onKeyPressed(lib::input::Key kEvent);
			virtual void onKeyReleased(lib::input::Key kEvent);

		private:
			std::vector<sptr<IMenuControl>> _controls;
		};
	}
}

#endif
