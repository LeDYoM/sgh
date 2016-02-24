#include <lib/include/types.hpp>
#include <lib/include/rect.hpp>
#include <lib/draw/transformation.hpp>
#include <lib/draw/renderstates.hpp>
#include <SFML/Graphics.hpp>

namespace lib
{
	sf::FloatRect convert(const lib::Rect<f32> &source);
	lib::Rect<f32> convert(const sf::FloatRect &source);

	sf::Transform convert(const lib::draw::Transformation &transform);
	sf::RenderStates convert(const lib::draw::RenderStates &renderStates);

}
