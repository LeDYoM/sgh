#ifndef __LIB_WINDOW_HPP__
#define __LIB_WINDOW_HPP__

#include <lib/include/types.hpp>
#include <lib/include/iapp.hpp>
#include "appservice.hpp"

namespace lib
{
	namespace drivers
	{
		namespace render
		{
			class RenderTarget;
		}
		namespace window
		{
			class IWWindow;
		}
	}
	namespace core
	{
		struct WindowPrivate;
		class AppController;

		struct WindowCreationParams
		{
			vector2du32 size{ 1024,768 };
			u32 bpp{ 16 };
			u32 antialiasing{ 0 };
			bool vsync{ false };
			bool fullScreen{ false };
			bool resizable{ false };
			bool titleBar{ true };
			str windowTitle;
			WindowCreationParams() = default;
		};

		class Window : SystemObject
		{
		public:
			Window(AppController *, sptr<drivers::window::IWWindow>);
			virtual ~Window();

			bool preLoop();
			bool postLoop();
			virtual void onCreate();
			virtual void onDestroy();
			void exitProgram();

			sptr<drivers::render::RenderTarget> windowRenderTarget() const;
			/* Driver communication */
			void wantsClose();
		private:

			uptr<WindowPrivate> p_wPrivate{ nullptr };
			bool m_shouldClose{ false };
		};
	}
}

#endif
