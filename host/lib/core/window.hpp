#ifndef __LIB_WINDOW_HPP__
#define __LIB_WINDOW_HPP__

#include <lib/include/types.hpp>
#include "appservice.hpp"
#include "renderwindow.hpp"

namespace lib
{
	struct WindowCreationParams;
	namespace draw
	{
		class View;
	}
	namespace core
	{
		struct WindowPrivate;
		class AppController;

		class Window : public AppService, public RenderWindow
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
