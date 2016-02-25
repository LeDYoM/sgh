#ifndef __LIB_EXTERNAL_REDNERWINDOW_HPP__
#define __LIB_EXTERNAL_REDNERWINDOW_HPP__

//#include <SFML/Graphics/RenderTarget.hpp>
//#include <SFML/Graphics/Image.hpp>
#include <lib/draw/rendertarget.hpp>
#include <SFML/Window/Window.hpp>
#include <string>

using namespace sf;

namespace lib
{
	namespace core
	{
		class RenderWindow : public sf::Window, public draw::RenderTarget
		{
		public:
			RenderWindow();
			virtual ~RenderWindow();

			virtual Vector2u getSize() const;
			//Image capture() const;
		protected:
			virtual void onResize();

		private:
			virtual bool activate(bool active);
		};
	}
}

#endif

