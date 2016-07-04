#ifndef __LIB_SCENE_HPP__
#define __LIB_SCENE_HPP__

#include <lib/core/compileconfig.hpp>
#include <lib/include/types.hpp>
#include <lib/include/key.hpp>
#include <lib/include/iappcontext.hpp>
#include <lib/core/timer.hpp>
#include <lib/core/inputreceiver.hpp>
#include "rendergroup.hpp"
#include "camera.hpp"
#include <string>

namespace lib
{
	class ResourceManager;
	class UtilProvider;
	namespace draw
	{
		namespace anim
		{
			class IAnimation;
		}
		class SceneManager;

		class LIB_API_EXPORT Scene : public RenderGroup, public InputReceiverNode
		{
		public:
			Scene(PIAppContext piAppContext, const std::string &_name);
			virtual ~Scene();

			virtual void onEnterScene() = 0;
			virtual void onExitScene() = 0;

			virtual void onKeyPressed(const Key &) override;
			virtual void onKeyReleased(const Key &) override;

			virtual const lib::vector2df getDefaultSizeView() = 0;
			virtual void update() = 0;

			sptr<lib::ResourceManager> resourceManager() const;
			sptr<UtilProvider> utilProvider() const;

			sptr<Camera> camera() const { return m_camera; }
			vector2df pointViewToCurrentView(const vector2df &point, const vector2df &size) const;

			void setNextScene(const std::string &name);
			void exitProgram();

			Timer clock;
//			inline const Rectf32 &currentView() const { return m_camera.target(); }
			virtual bool init() override;
			virtual bool deinit();



		protected:
			inline u32 state() const { return _state; }
			inline void setState(u32 ns) { _state = ns; }

			Scene *const parentScene() override final;

		private:
			void privateOnEnterScene();
			void privateOnExitScene();
			u32 _state;

			friend class SceneManager;
			sptr<Camera> m_camera;
		};
	}
}

#endif
