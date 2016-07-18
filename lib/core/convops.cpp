#include "convops.hpp"

namespace lib
{
	Rect<f32> convert(const sf::FloatRect &source)
	{
		return Rect<f32>{source.left, source.top, source.width, source.height};
	}

	sf::IntRect convert(const Rects32 &source)
	{
		return sf::IntRect(source.left, source.top, source.width, source.height);
	}

	sf::FloatRect convert(const Rectf32 &source)
	{
		return sf::FloatRect(source.left, source.top, source.width, source.height);
	}

	sf::Transform convert(const draw::Transformation &transform)
	{
		const draw::Transformation::TransformationDataType &f{ transform.matrix() };
		sf::Transform temp(f[0], f[4], /*f[8],*/ f[12],
			f[1], f[5], /*f[9],*/ f[13],
			/*f[2], f[6], f[10], f[14],*/
			f[3], f[7], /*f[11],*/ f[15]);

		return temp;
	}

	const sf::Vertex * convert(const draw::VertexArray &vertexArray)
	{
		return reinterpret_cast<const sf::Vertex*>(&(vertexArray[0]));
	}

	sf::PrimitiveType convert(const draw::PrimitiveType primitiveType)
	{
		return static_cast<sf::PrimitiveType>((int)primitiveType);
	}

}
