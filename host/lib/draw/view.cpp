#include <cmath>

#include "view.hpp"

#include <SFML/Graphics/View.hpp>

namespace lib
{
	namespace draw
	{
		View::View(const Rectf32 &rectangle) 
			: m_target{ rectangle } {}

		View::View(const vector2df &topLeft, const vector2df &size)
			: m_target{ topLeft,size } {}
	}
}
