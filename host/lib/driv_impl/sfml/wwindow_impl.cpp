#include "wwindow_impl.hpp"
#include <lib/core/convops.hpp>

namespace lib
{
	namespace drivers
	{
		namespace window
		{
			bool SFMLWindow::create(u32 width, u32 height, u32 bpp, const char *title, u32 depth, u32 stencil, u32 antialiasing, u32 major, u32 minor, u32 attributes)
			{
				sf::Window::create(sf::VideoMode{ width, height, bpp }, sf::String(title), sf::Style::Default, sf::ContextSettings{ depth, stencil, antialiasing, major, minor, attributes });
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
				sf::Window::setTitle(title);
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
				sf::RenderWindow::draw(convert(vertexArray), vertexArray.getVertexCount(), vertexArray.getPrimitiveType(), convert(states));
			}

			void SFMLWindow::setViewRectangle(const Rectf32 &rect)
			{
				sf::View view{ sf::FloatRect{ rect.left, rect.top, rect.width, rect.height } };
				setView(view);
			}

		}
	}
}

