#include "wwindow_impl.hpp"
#include <lib/drivers/render/rendertarget.hpp>
#include <lib/core/convops.hpp>
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

			bool SFMLWindow::create(u32 width, u32 height, u32 bpp, const char *title, u32 depth, u32 stencil, u32 antialiasing, u32 major, u32 minor, u32 attributes)
			{
				sf::Window::create(sf::VideoMode{ width, height, bpp }, getAsString(title), sf::Style::Default, sf::ContextSettings{ depth, stencil, antialiasing, major, minor, attributes });
				return true;
			}

			bool SFMLWindow::resizePending() const
			{
				return m_resizePending;
			}

			lib::vector2du32 SFMLWindow::size() const
			{
				return vector2du32();
			}

			void SFMLWindow::setVerticalSync(bool enabled)
			{
				sf::Window::setVerticalSyncEnabled(enabled);
			}

			void SFMLWindow::setTitle(const char *title)
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

