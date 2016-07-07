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
	namespace draw
	{
		class RenderTarget;
		class RenderStates
		{
		public:
			RenderStates();
			RenderStates(const RenderStates&) = default;
			RenderStates &operator=(const RenderStates&) = delete;
			explicit RenderStates(const sf::BlendMode &theBlendMode);
			explicit RenderStates(const Transformation &transformation);
			explicit RenderStates(const sf::Texture* theTexture);
			explicit RenderStates(const sf::Shader* theShader);
			explicit RenderStates(RenderTarget *theRenderTarget);
			RenderStates(const sf::BlendMode &theBlendMode, const Transformation &transformation,
				const sf::Texture *theTexture, const sf::Shader *theShader, draw::RenderTarget *theRenderTarget);

			Transformation transform;

			sf::BlendMode blendMode;
			const sf::Texture *texture;
			const sf::Shader *shader;
			draw::RenderTarget *currentTarget;
		};
	}
}

#endif
