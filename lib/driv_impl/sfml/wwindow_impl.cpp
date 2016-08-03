#include "wwindow_impl.hpp"
#include <lib/drivers/render/rendertarget.hpp>
#include "rendertarget_impl.hpp"
#include "texture_impl.hpp"
#include <lib/core/convops.hpp>
#include <lib/core/wcp.hpp>
#include <lib/core/window.hpp>
#include <lib/include/key.hpp>

namespace lib
{
	namespace drivers
	{
		namespace window
		{
			namespace
			{
				sf::String getAsString(const std::string &other)
				{
					std::wstring wsTmp(other.begin(), other.end());
					sf::String temp(wsTmp);
					return temp;
				}

				lib::Key doCast(const sf::Keyboard::Key &k)
				{
					int temp = k;
					return temp;
				}
			}

			bool SFMLWindow::create(const WindowCreationParams &wcp)
			{
				sf::Uint32 style{ sf::Style::None };
				if (wcp.titleBar)
					style |= sf::Style::Titlebar | sf::Style::Close;
				if (wcp.resizable)
					style |= sf::Style::Resize;
				if (wcp.fullScreen)
					style = sf::Style::Fullscreen;

				sf::Window::create(sf::VideoMode{ wcp.size.x, wcp.size.y, wcp.bpp }, getAsString(""), style, sf::ContextSettings{ 0, 0, wcp.antialiasing, 0, 0, 0 });
				m_thisAsRenderTarget = sptr<drivers::render::RenderTarget>(new drivers::render::SFMLRenderTarget(static_cast<sf::RenderTarget*>(this)));
				return true;
			}

			bool SFMLWindow::resizePending() const
			{
				return m_resizePending;
			}

			vector2du16 SFMLWindow::size() const
			{
				return vector2du16();
			}

			void SFMLWindow::setVerticalSync(bool enabled)
			{
				sf::Window::setVerticalSyncEnabled(enabled);
			}

			void SFMLWindow::setTitle(const str &title)
			{
				sf::Window::setTitle(getAsString(title));
			}

			void SFMLWindow::clear()
			{
				sf::RenderWindow::clear();
			}

			void SFMLWindow::display()
			{
				sf::Window::display();
			}

			sptr<render::RenderTarget> SFMLWindow::windowRenderTarget() const
			{
				return m_thisAsRenderTarget;
			}

			sptr<render::Texture> SFMLWindow::newTexture(const str & fileName) const
			{
				return sptr<render::Texture>(new render::SFMLTexture);
			}

			void SFMLWindow::collectEvents()
			{
				sf::Event e;
				while (sf::Window::pollEvent(e))
				{
					sptr<DataMap> event_{ new DataMap() };
					bool correctEvent{ true };
					if (e.type == sf::Event::Closed)
					{
						(*event_)["Type"] = DataValue{ "Window" };
						(*event_)["Action"] = DataValue{ "WantsClose" };
//						window->wantsClose();
					}
					else if (e.type == sf::Event::KeyPressed || e.type == sf::Event::KeyReleased)
					{
						(*event_)["Type"] = DataValue{ "Input" };
						(*event_)["SubType"] = DataValue{ "Keyboard" };
						(*event_)["Device"] = DataValue{ u8{ 0 } };
						(*event_)["Action"] = DataValue{ e.type == sf::Event::KeyPressed ? u8{0} : u8{1} };
						(*event_)["Key"] = DataValue{ doCast(e.key.code).codetos32() };
//						window->receiveKeyEvent(event_);
					}
					else
					{
						correctEvent = false;
					}

					if (correctEvent)
					{
						m_collectedEvents.push(event_);
					}
				}
			}

			sptr<DataMap> SFMLWindow::nextEvent()
			{
				if (m_collectedEvents.empty())
					return nullptr;

				auto next = m_collectedEvents.front();
				m_collectedEvents.pop();
				return next;
			}

			u32 SFMLWindow::pendingEvents()
			{
				return m_collectedEvents.size();
			}
		}
	}
}

