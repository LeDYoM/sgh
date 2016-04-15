#include "renderstates.hpp"
#include <cstddef>

namespace lib
{
	namespace draw
	{
//		const RenderStates RenderStates::Default(sf::BlendMode(
//			sf::BlendMode::SrcAlpha, sf::BlendMode::OneMinusSrcAlpha, sf::BlendMode::Add,
//			sf::BlendMode::One, sf::BlendMode::OneMinusSrcAlpha, sf::BlendMode::Add));

		RenderStates::RenderStates()
			: RenderStates{ sf::BlendAlpha, {}, nullptr, nullptr } {}


		RenderStates::RenderStates(const Transformation &transformation)
			: RenderStates{ sf::BlendAlpha, transformation, nullptr, nullptr } {}

		RenderStates::RenderStates(const sf::BlendMode &theBlendMode)
			: RenderStates{ theBlendMode, {}, nullptr, nullptr } {}

		RenderStates::RenderStates(const sf::Texture* theTexture)
			: RenderStates{ sf::BlendAlpha, {}, theTexture, nullptr } {}

		RenderStates::RenderStates(const sf::Shader* theShader)
			: RenderStates{ sf::BlendAlpha, {}, nullptr, theShader } {}

		RenderStates::RenderStates(const sf::BlendMode &theBlendMode, const Transformation &transformation,
			const sf::Texture* theTexture, const sf::Shader* theShader) 
			: blendMode{ theBlendMode }, transform{ transformation }, texture{ theTexture }, shader{ theShader } {}

		void RenderStates::nextFrame()
		{
			reset();
		}

		void RenderStates::reset()
		{
			blendMode = sf::BlendAlpha;
			transform = Transformation{};
			texture = nullptr;
			shader = nullptr;
		}

	}
}
