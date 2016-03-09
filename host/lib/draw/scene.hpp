#ifndef __LIB_SCENE_HPP__
#define __LIB_SCENE_HPP__

#include "hasname.hpp"
#include <lib/core/compileconfig.hpp>
#include <lib/include/types.hpp>
#include <lib/include/key.hpp>
#include <lib/core/timer.hpp>
#include "iscenecontroller.hpp"
#include "rendergroup.hpp"
#include "camera.hpp"
#include <string>

namespace lib
{
	namespace core
	{
		class ResourceManager;
	}
	namespace util
	{
		class UtilProvider;
	}
	namespace draw
	{
		namespace anim
		{
			class IAnimation;
		}
		class SceneManager;

		class Scene : public draw::RenderGroup, public ISceneController
		{
		public:
			Scene(const std::string &_name);
			virtual ~Scene();

			virtual void onKeyPressed(input::Key key);
			virtual void onKeyReleased(input::Key key);

			void setNextScene(const std::string &name);

			uptr<core::ResourceManager> const &resourceManager();
			uptr<util::UtilProvider> const &utilProvider();

			const vector2df getCoordinatesToCenter(const Rectf32 &coordinates) const;
			inline const Camera &camera() const { return m_camera; }
			vector2df pointViewToCurrentView(const vector2df &point, const vector2df &size) const;

			void exitProgram();

		protected:
			void updateView();
			inline u32 state() const { return _state; }
			inline void setState(u32 ns) { _state = ns; }

			Timer clock;
		private:
			void privateOnInit();
			void privateOnDeinit();
			void privateOnEnterScene();
			void privateOnExitScene();

			lib::draw::Camera m_camera;
			u32 _state;

			SceneManager *p_scnManager;
			friend class SceneManager;
		};
	}
}

#endif
