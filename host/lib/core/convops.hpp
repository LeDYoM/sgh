#include <lib/include/types.hpp>
#include <lib/include/rect.hpp>
#include <SFML/Graphics.hpp>

namespace lib
{
	sf::FloatRect convert(const lib::Rect<f32> &source);
	lib::Rect<f32> convert(const sf::FloatRect &source);

}
