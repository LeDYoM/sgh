#ifndef LIB_DRIVERS_SFML_WWINDOW_IMPLEMENTATION_HPP
#define LIB_DRIVERS_SFML_WWINDOW_IMPLEMENTATION_HPP

#include <lib/drivers/window/wwindow.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

namespace lib
{
	namespace drivers
	{
		namespace window
		{
			class SFMLWindow : public IWWindow, public sf::RenderWindow
			{
				virtual bool create(u32 width, u32 height, u32 bpp, const char *title, u32 depth, u32 stencil, u32 antialiasing, u32  major, u32 minor, u32 attributes) override;
				virtual bool resizePending() const override;
				virtual vector2du32 size() const override;
				virtual void setVerticalSync(bool enabled) override;
				virtual void setTitle(const char *title) override;
				virtual void clear() override;
				virtual void display() override;
				virtual void draw(const draw::VertexArray &vertexArray, const draw::RenderStates& states) override;
				virtual void setViewRectangle(const Rectf32 &rect) override;
				virtual void receiveEvent(core::Window *const window);
			private:
				bool m_resizePending;
			};
		}
	}
}
#endif
