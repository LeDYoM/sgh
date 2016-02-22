#include "convops.hpp"

namespace lib
{
	sf::FloatRect lib::convert(const Rect<f32> &source)
	{
		return sf::FloatRect(source.origin(), source.size());
	}

	Rect<f32> lib::convert(const sf::FloatRect &source)
	{
		return Rect<f32>{source.left, source.top, source.width, source.height};
	}
}