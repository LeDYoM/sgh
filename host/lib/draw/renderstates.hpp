#ifndef LIB_DRAW_RENDERSTATES_HPP
#define LIB_DRAW_RENDERSTATES_HPP

#include <SFML/Graphics/BlendMode.hpp>
#include <SFML/Graphics/Transform.hpp>

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
			RenderStates(const sf::Transform &theTransform);
			RenderStates(const sf::Texture* theTexture);
			RenderStates(const sf::Shader* theShader);
			RenderStates(const sf::BlendMode &theBlendMode, const sf::Transform &theTransform,
				const sf::Texture *theTexture, const sf::Shader *theShader);
			static const RenderStates Default; ///< Special instance holding the default render states

			sf::BlendMode blendMode;
			sf::Transform transform;
			const sf::Texture* texture;
			const sf::Shader*  shader;
		};
	}
}

#endif
