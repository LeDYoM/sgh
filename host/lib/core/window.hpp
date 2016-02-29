#ifndef __LIB_WINDOW_HPP__
#define __LIB_WINDOW_HPP__

#include <lib/include/types.hpp>
#include "appservice.hpp"
#include "renderwindow.hpp"

#include <SFML/Window/Event.hpp>

namespace lib
{
	struct WindowCreationParams;
	namespace draw
	{
		class View;
	}
	namespace drivers
	{
		namespace window
		{
			class IRenderTarget;
		}
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

			void updateView(const draw::View &view);
			sptr<RenderTarget> renderTarget();
		private:
			void create(const WindowCreationParams &wcp);
			void keyEvent(sf::Event e);

			uptr<WindowPrivate> p_wPrivate{ nullptr };
			bool _shouldClose{ false };
			std::string _title;
		};
	}
}

#endif
