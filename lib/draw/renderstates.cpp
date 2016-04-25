#include "renderstates.hpp"
#include "../core/rendertarget.hpp"
#include <lib/include/types.hpp>
#include <cstddef>

namespace lib
{
	namespace draw
	{
//		const RenderStates RenderStates::Default(sf::BlendMode(
//			sf::BlendMode::SrcAlpha, sf::BlendMode::OneMinusSrcAlpha, sf::BlendMode::Add,
//			sf::BlendMode::One, sf::BlendMode::OneMinusSrcAlpha, sf::BlendMode::Add));

		RenderStates::RenderStates()
			: RenderStates{ sf::BlendAlpha, {}, nullptr, nullptr, nullptr } {}


		RenderStates::RenderStates(const Transformation &transformation)
			: RenderStates{ sf::BlendAlpha, transformation, nullptr, nullptr, nullptr } {}

		RenderStates::RenderStates(const sf::BlendMode &theBlendMode)
			: RenderStates{ theBlendMode, {}, nullptr, nullptr, nullptr } {}

		RenderStates::RenderStates(const sf::Texture* theTexture)
			: RenderStates{ sf::BlendAlpha, {}, theTexture, nullptr, nullptr } {}

		RenderStates::RenderStates(const sf::Shader* theShader)
			: RenderStates{ sf::BlendAlpha, {}, nullptr, theShader, nullptr } {}

		RenderStates::RenderStates(core::RenderTarget *theRenderTarget)
			: RenderStates{ sf::BlendAlpha, {}, nullptr, nullptr, theRenderTarget } {}

		RenderStates::RenderStates(const sf::BlendMode &theBlendMode, const Transformation &theTransformation,
			const sf::Texture *theTexture, const sf::Shader *theShader, core::RenderTarget *theRenderTarget) 
			: blendMode{ theBlendMode }, transform{ theTransformation }, texture{ theTexture }, shader{theShader}
		{}
	}
}
