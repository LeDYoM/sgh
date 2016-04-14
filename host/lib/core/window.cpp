#include <locale>
#include "window.hpp"
#include "compileconfig.hpp"
#include "log.hpp"
#include "timer.hpp"
#include "appcontroller.hpp"
#include <lib/include/iapp.hpp>
#include "events/event.hpp"
#include "events/inputevent.hpp"
#include "servicesmanager.hpp"
#include <lib/draw/camera.hpp>
#include <lib/driv_impl/sfml/wwindow_impl.hpp>
#include "appcontroller.hpp"
#include "driver.hpp"

namespace lib
{
	namespace core
	{
		struct WindowPrivate
		{
			Timer globalClock;
			u64 lastTimeFps{ 0 };
			s32 lastFps{ 0 };
			s32 currentFps{ 0 };
			sptr<drivers::window::IWWindow> m_renderWindow{ nullptr };
		};
		Window::Window(const WindowCreationParams &wcp)
			: p_wPrivate{ new WindowPrivate() }, m_wcp{ wcp }, _title(wcp.windowTitle)
		{
			LOG_CONSTRUCT_NOPARAMS;
		}

		Window::~Window()
		{
			LOG_DESTRUCT_NOPARAMS;
		}

		void Window::Init()
		{
			create(m_wcp);
		}

		void Window::create(const WindowCreationParams &wcp)
		{
			LOG_DEBUG("Going to create Window");
			LOG_DEBUG("Resolution:" << wcp.width << "x" << wcp.height << "x" << std::to_string(wcp.bpp));
			LOG_DEBUG("Fullscreen:" << wcp.fullScreen);
			LOG_DEBUG("Antialiasing:" << wcp.antialiasing);

			sf::Uint32 style{ sf::Style::Titlebar | sf::Style::Close };
			if (wcp.fullScreen)
				style = sf::Style::Fullscreen;

			p_wPrivate->m_renderWindow = appController()->driver()->newWindow(); //sptr<drivers::window>{new RenderWindow()};
			p_wPrivate->m_renderWindow->create(wcp.width, wcp.height, wcp.bpp, _title.c_str(), 0, 0, 0, 0, 0, 0);

			p_wPrivate->m_renderWindow->setVerticalSync(wcp.vsync);
		}

		bool Window::preLoop()
		{
			auto eMs = p_wPrivate->globalClock.getElapsedTime().asMilliSeconds();
			if ((eMs - p_wPrivate->lastTimeFps) > 1000)
			{
				p_wPrivate->lastTimeFps = eMs;
				p_wPrivate->lastFps = p_wPrivate->currentFps;
				p_wPrivate->currentFps = 0;
				p_wPrivate->m_renderWindow->setTitle(std::string(_title + " FPS:" + std::to_string(p_wPrivate->lastFps) ).c_str());
			}
			++(p_wPrivate->currentFps);
			p_wPrivate->m_renderWindow->clear();
			p_wPrivate->m_renderWindow->collectEvents();

			while (p_wPrivate->m_renderWindow->pendingEvents())
			{
				sptr<DataMap> pEvent{ p_wPrivate->m_renderWindow->nextEvent() };
				if (pEvent)
				{
					const std::string &eType( pEvent->at("Type").getString() );
					if ( eType == "Input")
					{

					}
					else if (eType == "Window")
					{
						_shouldClose = true;
					}
				}
			}
			/*
			sf::Event event;
			while (p_wPrivate->m_renderWindow->pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
				{
					return true;
				}
				else if (event.type == sf::Event::KeyPressed || event.type == sf::Event::KeyReleased)
				{
					keyEvent(event);
				}
			}
			*/

			return _shouldClose;
		}

		bool Window::postLoop()
		{
			p_wPrivate->m_renderWindow->display();
			return _shouldClose;
		}

		void Window::onCreate()
		{
			LOG_DEBUG("Window created");
		}

		void Window::onDestroy()
		{
			LOG_DEBUG("Going to close Window");
//			p_wPrivate->m_renderWindow->close();
			LOG_DEBUG("Window closed");
		}

		void Window::wantsClose()
		{
			_shouldClose = true;
		}

		void Window::exitProgram()
		{
			_shouldClose = true;
		}

		void Window::updateCamera(const draw::Camera &camera)
		{
			p_wPrivate->m_renderWindow->setViewRectangle(camera.target());
		}

		sptr<RenderTarget> Window::renderTarget()
		{
			return p_wPrivate->m_renderWindow;
		}
	}
}
