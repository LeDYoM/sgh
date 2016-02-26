#include "convops.hpp"

namespace lib
{
	/*
	sf::FloatRect convert(const lib::Rect<f32> &source)
	{
		return sf::FloatRect(source.origin(), source.size());
	}
	*/

	Rect<f32> convert(const sf::FloatRect &source)
	{
		return Rect<f32>{source.left, source.top, source.width, source.height};
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

	sf::RenderStates convert(const draw::RenderStates &renderStates)
	{
		return sf::RenderStates{ renderStates.blendMode, convert(renderStates.transform), renderStates.texture, renderStates.shader };
	}

	const sf::Vertex * convert(const draw::VertexArray &vertexArray)
	{
		return reinterpret_cast<const sf::Vertex*>(&(vertexArray[0]));
	}
}
