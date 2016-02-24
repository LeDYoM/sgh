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

	sf::Transform convert(const draw::Transformation &transform)
	{
		const draw::Transformation::TransformationDataType &f{ transform.getMatrix() };
		sf::Transform temp( f[0], f[4], /*f[8],*/ f[12], 
							f[1], f[5], /*f[9],*/ f[13], 
							/*f[2], f[6], f[10], f[14],*/
							f[3], f[7], /*f[11],*/ f[15] );

		return temp;
	}

	sf::RenderStates convert(const draw::RenderStates &renderStates)
	{
		return sf::RenderStates{ renderStates.blendMode, renderStates.transform, renderStates.texture, renderStates.shader };
	}

}