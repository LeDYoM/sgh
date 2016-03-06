#include "wwindow_impl.hpp"
#include <lib/core/convops.hpp>
#include <lib/core/window.hpp>
#include <lib/include/key.hpp>
#include <lib/core/events/inputevent.hpp>

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

				lib::input::Key doCast(const sf::Keyboard::Key &k)
				{
					int temp = k;
					return static_cast<lib::input::Key>(temp);
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

			void SFMLWindow::draw(const draw::VertexArray &vertexArray, const draw::RenderStates& states)
			{
				sf::RenderWindow::draw(convert(vertexArray), vertexArray.getVertexCount(), convert(vertexArray.getPrimitiveType()), convert(states));
			}

			void SFMLWindow::setViewRectangle(const Rectf32 &rect)
			{
				sf::View view{ sf::FloatRect{ rect.left, rect.top, rect.width, rect.height } };
				setView(view);
			}

			void SFMLWindow::receiveEvent(core::Window *const window)
			{
				sf::Event e;
				while (sf::Window::pollEvent(e))
				{
					if (e.type == sf::Event::Closed)
					{
						window->wantsClose();
					}
					else if (e.type == sf::Event::KeyPressed || e.type == sf::Event::KeyReleased)
					{
						core::events::KeyEvent event_{e.type == sf::Event::KeyPressed ? 
							core::events::KeyEvent::Action::KeyPressed : core::events::KeyEvent::Action::KeyReleased,
							doCast(e.key.code)
						};

						window->receiveKeyEvent(event_);
					}
				}
			}
		}
	}
}

