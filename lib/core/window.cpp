#include <locale>
#include "window.hpp"
#include "compileconfig.hpp"
#include "log.hpp"
#include "timer.hpp"
#include "appcontroller.hpp"
#include <lib/include/iapp.hpp>
#include "servicesmanager.hpp"
#include <lib/driv_impl/sfml/wwindow_impl.hpp>
#include <lib/driv_impl/sfml/rendertarget_impl.hpp>
#include "appcontroller.hpp"
#include "driver.hpp"
#include "input.hpp"

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
		Window::Window(AppController *m_appController, sptr<drivers::window::IWWindow> drvWindow)
			: SystemObject{ m_appController }, p_wPrivate {	new WindowPrivate()	}
		{
			LOG_CONSTRUCT_NOPARAMS;
//			LOG_DEBUG("Going to create Window");
//			LOG_DEBUG("Resolution:" << wcp.size.x << "x" << wcp.size.y << "x" << std::to_string(wcp.bpp));
//			LOG_DEBUG("Fullscreen:" << wcp.fullScreen);
//			LOG_DEBUG("Antialiasing:" << wcp.antialiasing);

			p_wPrivate->m_renderWindow = drvWindow;
			//			p_wPrivate->m_renderWindow->create(wcp);

//			p_wPrivate->m_renderWindow->setVerticalSync(wcp.vsync);
		}

		Window::~Window()
		{
			LOG_DESTRUCT_NOPARAMS;
		}

		bool Window::preLoop()
		{
			auto eMs = p_wPrivate->globalClock.getElapsedTime().asMilliSeconds();
			if ((eMs - p_wPrivate->lastTimeFps) > 1000)
			{
				p_wPrivate->lastTimeFps = eMs;
				p_wPrivate->lastFps = p_wPrivate->currentFps;
				p_wPrivate->currentFps = 0;
				p_wPrivate->m_renderWindow->setTitle(std::string(" FPS:" + std::to_string(p_wPrivate->lastFps) ).c_str());
			}
			++(p_wPrivate->currentFps);
			p_wPrivate->m_renderWindow->collectEvents();

			service<Input>()->nextFrame();
			while (p_wPrivate->m_renderWindow->pendingEvents())
			{
				sptr<DataMap> pEvent{ p_wPrivate->m_renderWindow->nextEvent() };
				if (pEvent)
				{
					const std::string &eType( pEvent->at("Type").getString() );
					if ( eType == "Input") {
						service<Input>()->processSystemEvent(pEvent);
					}
					else if (eType == "Window") {
						m_shouldClose = true;
					}
				}
			}
			p_wPrivate->m_renderWindow->clear();
			return m_shouldClose;
		}

		bool Window::postLoop()
		{
			p_wPrivate->m_renderWindow->display();
			return m_shouldClose;
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
			m_shouldClose = true;
		}

		void Window::exitProgram()
		{
			m_shouldClose = true;
		}
		sptr<drivers::render::RenderTarget> Window::windowRenderTarget() const
		{
			return p_wPrivate->m_renderWindow->windowRenderTarget();
		}
	}
}
