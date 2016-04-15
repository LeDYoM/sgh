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
			RenderStates(const sf::Texture* theTexture);
			RenderStates(const sf::Shader* theShader);
			RenderStates(const sf::BlendMode &theBlendMode, const Transformation &transformation,
				const sf::Texture *theTexture, const sf::Shader *theShader);
			RenderStates(const RenderStates&) = delete;
			RenderStates &operator=(const RenderStates&) = delete;

			void nextFrame();
			void reset();

			Transformation transform;

			sf::BlendMode blendMode;
			const sf::Texture *texture;
			const sf::Shader *shader;
			sptr<core::RenderTarget> currentTarget;
		};
	}
}

#endif
