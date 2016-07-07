#include <lib/include/types.hpp>
#include <lib/draw/transformation.hpp>
#include <lib/draw/renderstates.hpp>
#include <lib/draw/vertexarray.hpp>
#include <lib/draw/vertex.hpp>
#include <SFML/Graphics/Vertex.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Transform.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/PrimitiveType.hpp>
#include <SFML/System/Vector2.hpp>

namespace lib
{
	/*
	sf::FloatRect convert(const lib::Rect<f32> &source);
	*/

	Rect<f32> convert(const sf::FloatRect &source);

	sf::IntRect convert(const Rects32 &);
	sf::FloatRect convert(const Rectf32 &);
	sf::Transform convert(const draw::Transformation &transform);
	sf::RenderStates convert(const draw::RenderStates &renderStates);
	const sf::Vertex * convert(const draw::VertexArray &vertexArray);
	sf::PrimitiveType convert(const draw::PrimitiveType primitiveType);

	template <typename T>
	const sf::Vector2<T> convert(const vector2d<T> &v)
	{
		return sf::Vector2<T>(v.x, v.y);
	}

	template <typename T>
	const vector2d<T> convert(const sf::Vector2<T> &v)
	{
		return vector2d<T>(v.x, v.y);
	}
}
