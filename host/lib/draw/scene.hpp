#ifndef __LIB_SCENE_HPP__
#define __LIB_SCENE_HPP__

#include "hasname.hpp"
#include <lib/core/compileconfig.hpp>
#include <lib/include/types.hpp>
#include <lib/include/key.hpp>
#include <lib/core/timer.hpp>
#include "iscene.hpp"
#include "rendergroup.hpp"
#include "camera.hpp"
#include <string>

namespace lib
{
	namespace core
	{
		class ResourceManager;
		namespace events
		{
			class EventClient;
		}
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

		class SceneHandle
		{
		public:
			SceneManager *p_scnManager;
			friend class SceneManager;

			uptr<core::ResourceManager> const &resourceManager();
			uptr<util::UtilProvider> const &utilProvider();

			const vector2df getCoordinatesToCenter(const Rectf32 &coordinates) const;
			inline const Camera &camera() const { return m_camera; }
			vector2df pointViewToCurrentView(const vector2df &point, const vector2df &size) const;

			void setNextScene(const std::string &name);
			void exitProgram();

			Timer clock;
			core::events::EventClient *eventClient();
		protected:
			void updateView();
		private:
			lib::draw::Camera m_camera;
			friend class Scene;
		};

		class Scene : public draw::RenderGroup, public IScene
		{
		public:
			Scene(const std::string &_name);
			virtual ~Scene();

			virtual void onPrivateKeyPressed(input::Key key);
			virtual void onPrivateKeyReleased(input::Key key);

			virtual void onKeyPressed(input::Key key) = 0;
			virtual void onKeyReleased(input::Key key) = 0;

			SceneHandle *sceneHandle;

		protected:
			inline u32 state() const { return _state; }
			inline void setState(u32 ns) { _state = ns; }
		private:
			sptr<core::events::EventClient> m_eventClient{ nullptr };

			void privateOnInit();
			void privateOnDeinit();
			void privateOnEnterScene();
			void privateOnExitScene();
			u32 _state;

			friend class SceneManager;
		};
	}
}

#endif
