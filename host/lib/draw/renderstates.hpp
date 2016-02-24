#ifndef LIB_DRAW_RENDERSTATES_HPP
#define LIB_DRAW_RENDERSTATES_HPP

#include <SFML/Graphics/BlendMode.hpp>
//#include <SFML/Graphics/Transform.hpp>
#include "transformation.hpp"

namespace sf
{
	class Shader;
	class Texture;

}

namespace lib
{
	namespace draw
	{
		class RenderStates
		{
		public:
			RenderStates();
			RenderStates(const sf::BlendMode &theBlendMode);
			RenderStates(const Transformation &transformation);
			RenderStates(const sf::Texture* theTexture);
			RenderStates(const sf::Shader* theShader);
			RenderStates(const sf::BlendMode &theBlendMode, const Transformation &transformation,
				const sf::Texture *theTexture, const sf::Shader *theShader);
			static const RenderStates Default;

			sf::BlendMode blendMode;
			Transformation transform;
			const sf::Texture* texture;
			const sf::Shader*  shader;
		};
	}
}

#endif
