#include <cmath>

#include "view.hpp"

#include <SFML/Graphics/View.hpp>

namespace lib
{
	namespace draw
	{
		View::View() : m_target{ 0,0,1000,1000 } {}
		View::View(const Rectf32 &rectangle) : m_target{ rectangle } {}
		View::View(const vector2df &topLeft, const vector2df &size) : m_target{ topLeft,size } {}

		void View::setSize(const vector2df &size)
		{
			m_target.width = size.x;
			m_target.height = size.y;
		}

	}
}
