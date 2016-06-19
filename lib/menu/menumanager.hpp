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
		class MenuTheme;
		class MenuManager : public draw::Scene
		{
		public:
			MenuManager(draw::SceneManager *const pSceneManager, const std::string &name);
			virtual ~MenuManager();

			virtual bool init() override;
			void addMenuStep(sptr<MenuStep> step);

			void start(sptr<MenuStep> firstStep);
			void start(const std::string &firstStep);
			void changeStep(const std::string &step);
			void changeStep(sptr<MenuStep> step);
			virtual void onKeyPressed(Key key);
			virtual void onKeyReleased(Key key);

			sptr<MenuTheme> const &menuTheme() const { return m_mTheme; }

		private:
			void setActiveStep(sptr<MenuStep> step);
			sptr<MenuStep> _activeMenuStep{ nullptr };
			sptr<MenuTheme> m_mTheme{ nullptr };
		};
	}
}

#endif
