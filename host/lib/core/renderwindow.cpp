#include "renderwindow.hpp"
//#include <SFML/Graphics/GLCheck.hpp>


namespace lib
{
	namespace core
	{

		RenderWindow::RenderWindow() {}
		RenderWindow::~RenderWindow() {}

		bool RenderWindow::activate(bool active)
		{
			return setActive(active);
		}

		Vector2u RenderWindow::getSize() const
		{
			return Window::getSize();
		}

		/*
		Image RenderWindow::capture() const
		{
		Image image;
		if (setActive())
		{
		int width = static_cast<int>(getSize().x);
		int height = static_cast<int>(getSize().y);

		// copy rows one by one and flip them (OpenGL's origin is bottom while SFML's origin is top)
		std::vector<Uint8> pixels(width * height * 4);
		for (int i = 0; i < height; ++i)
		{
		Uint8* ptr = &pixels[i * width * 4];
		glCheck(glReadPixels(0, height - i - 1, width, 1, GL_RGBA, GL_UNSIGNED_BYTE, ptr));
		}

		image.create(width, height, &pixels[0]);
		}

		return image;
		}
		*/

		void RenderWindow::onResize()
		{
			// Update the current view (recompute the view port, which is stored in relative coordinates)
			setView(getView());
		}
	}
}
