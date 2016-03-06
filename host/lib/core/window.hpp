#ifndef __LIB_WINDOW_HPP__
#define __LIB_WINDOW_HPP__

#include <lib/include/types.hpp>
#include <lib/include/iapp.hpp>
#include "appservice.hpp"

#include "events/inputevent.hpp"

namespace lib
{
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
			Window(const WindowCreationParams &wcp);
			virtual ~Window();
			void Init() override;
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
			WindowCreationParams m_wcp;
			uptr<WindowPrivate> p_wPrivate{ nullptr };
			bool _shouldClose{ false };
			std::string _title;
		};
	}
}

#endif
