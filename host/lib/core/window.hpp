#ifndef __LIB_WINDOW_HPP__
#define __LIB_WINDOW_HPP__

#include <lib/include/types.hpp>
#include "appservice.hpp"

#include "events/inputevent.hpp"

namespace lib
{
	struct WindowCreationParams;
	namespace draw
	{
		class Camera;
	}
	namespace core
	{
		struct WindowPrivate;
		class AppController;
		class RenderTarget;

		class Window : public AppService
		{
		public:
			Window(AppController *const appController, const WindowCreationParams &wcp);
			virtual ~Window();
			bool preLoop();
			bool postLoop();
			virtual void onCreate();
			virtual void onDestroy();
			void exitProgram();

			void updateCamera(const draw::Camera &camera);
			sptr<RenderTarget> renderTarget();

			/* Driver communication */
			void receiveKeyEvent(const events::KeyEvent &e);
			void wantsClose();
		private:
			void create(const WindowCreationParams &wcp);

			uptr<WindowPrivate> p_wPrivate{ nullptr };
			bool _shouldClose{ false };
			std::string _title;
		};
	}
}

#endif
