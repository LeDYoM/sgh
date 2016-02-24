#include <lib/include/types.hpp>
#include <lib/include/rect.hpp>
#include <lib/draw/transformation.hpp>
#include <lib/draw/renderstates.hpp>
#include <lib/draw/vertexarray.hpp>
#include <lib/draw/vertex.hpp>
#include <SFML/Graphics/Vertex.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Transform.hpp>
#include <SFML/Graphics/RenderStates.hpp>

namespace lib
{
	sf::FloatRect convert(const lib::Rect<f32> &source);
	lib::Rect<f32> convert(const sf::FloatRect &source);

	sf::Transform convert(const lib::draw::Transformation &transform);
	sf::RenderStates convert(const lib::draw::RenderStates &renderStates);
	const sf::Vertex *convert(const lib::draw::VertexArray &vertexArray);
}
