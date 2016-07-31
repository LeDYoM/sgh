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
		class ISceneController;

		class LIB_API Scene : public RenderGroup, public InputReceiverNode
		{
		public:
			Scene(PIAppContext piAppContext, const std::string &_name);
			virtual ~Scene();

			virtual void onEnterScene() = 0;
			virtual void onExitScene() = 0;

			virtual void onKeyPressed(const Key &) override;
			virtual void onKeyReleased(const Key &) override;

			virtual const vector2df getDefaultSizeView() = 0;
			virtual void update() = 0;

			sptr<ResourceManager> resourceManager() const;
			sptr<UtilProvider> utilProvider() const;

			sptr<Camera> camera() const { return m_camera; }
			vector2df pointViewToCurrentView(const vector2df &point, const vector2df &size) const;

			void setNextScene(const str &name);
			void exitProgram();

			Timer clock;
			virtual bool init() override;
			virtual bool deinit();

		protected:
			inline u32 state() const { return _state; }
			inline void setState(u32 ns) { _state = ns; }

		private:
			u32 _state;

			friend class SceneManager;
			sptr<Camera> m_camera;

			sptr<ISceneController> m_controller;
		};
	}
}

#endif
