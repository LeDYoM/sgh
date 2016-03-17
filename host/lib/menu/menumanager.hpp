#ifndef __LIB_MENUMANAGER_HPP__
#define __LIB_MENUMANAGER_HPP__

#include <vector>
#include <lib/include/types.hpp>
#include <lib/draw/scene.hpp>

namespace lib
{
	namespace menu
	{
		class MenuStep;
		class MenuManager : public draw::Scene
		{
		public:
			MenuManager(const std::string &name);
			virtual ~MenuManager();

			void addMenuStep(sptr<MenuStep> step);

			void start(sptr<MenuStep> firstStep);
			void start(const std::string &firstStep);
			void changeStep(const std::string &step);
			void changeStep(sptr<MenuStep> step);
			virtual void onKeyPressed(input::Key key);
			virtual void onKeyReleased(input::Key key);

		private:
			void setActiveStep(sptr<MenuStep> step);

			sptr<MenuStep> _activeMenuStep{ nullptr };
		};
	}
}

#endif
