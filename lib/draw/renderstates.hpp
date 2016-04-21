#ifndef LIB_DRAW_RENDERSTATES_HPP
#define LIB_DRAW_RENDERSTATES_HPP

#include <SFML/Graphics/BlendMode.hpp>
#include "transformation.hpp"

namespace sf
{
	class Shader;
	class Texture;

}

namespace lib
{
	namespace core
	{
		class RenderTarget;
	}
	namespace draw
	{
		class RenderStates
		{
		public:
			RenderStates();
			RenderStates(const sf::BlendMode &theBlendMode);
			RenderStates(const Transformation &transformation);
			RenderStates(sf::Texture* theTexture);
			RenderStates(sf::Shader* theShader);
			RenderStates(const sf::BlendMode &theBlendMode, const Transformation &transformation,
				sf::Texture *theTexture, sf::Shader *theShader);
			RenderStates(const RenderStates&) = default;
			RenderStates &operator=(const RenderStates&) = default;

			void nextFrame();
			void reset();

			Transformation transform;

			sf::BlendMode blendMode;
			sf::Texture *texture;
			sf::Shader *shader;
			sptr<core::RenderTarget> currentTarget;
		};
	}
}

#endif
