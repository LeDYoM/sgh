#ifndef __LIB_WINDOW_HPP__
#define __LIB_WINDOW_HPP__

#include <lib/include/types.hpp>
#include <lib/include/iapp.hpp>
#include "appservice.hpp"

namespace lib
{
	namespace draw
	{
		class RenderTarget;
	}
	namespace drivers
	{
		namespace render
		{
			class RenderTarget;
		}
	}
	namespace core
	{
		struct WindowPrivate;
		class AppController;

		class Window : public AppService
		{
		public:
			Window(const WindowCreationParams &wcp);
			virtual ~Window();
			static const str staticTypeName() { return "Window"; }

			void Init() override;
			bool preLoop();
			bool postLoop();
			virtual void onCreate();
			virtual void onDestroy();
			void exitProgram();

			sptr<drivers::render::RenderTarget> windowRenderTarget() const;
			/* Driver communication */
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
