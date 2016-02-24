#include "renderstates.hpp"
#include <cstddef>

namespace lib
{
	namespace draw
	{
		const RenderStates RenderStates::Default(sf::BlendMode(
			sf::BlendMode::SrcAlpha, sf::BlendMode::OneMinusSrcAlpha, sf::BlendMode::Add,
			sf::BlendMode::One, sf::BlendMode::OneMinusSrcAlpha, sf::BlendMode::Add));

		RenderStates::RenderStates()
			: blendMode{ sf::BlendAlpha }, transform{}, texture{ nullptr }, shader{ nullptr } {}


		RenderStates::RenderStates(const Transformation &transformation)
			: blendMode{ sf::BlendAlpha }, transform{ transformation }, texture{ nullptr }, shader{ nullptr } {}

		RenderStates::RenderStates(const sf::BlendMode &theBlendMode)
			: blendMode{ theBlendMode }, transform{}, texture{ nullptr }, shader{ nullptr } {}

		RenderStates::RenderStates(const sf::Texture* theTexture)
			: blendMode{ sf::BlendAlpha }, transform{}, texture{ theTexture }, shader{ nullptr } {}

		RenderStates::RenderStates(const sf::Shader* theShader)
			: blendMode{ sf::BlendAlpha }, transform{}, texture{ nullptr }, shader{ theShader } {}

		RenderStates::RenderStates(const sf::BlendMode& theBlendMode, const Transformation &transformation,
			const sf::Texture* theTexture, const sf::Shader* theShader) 
			: blendMode{ theBlendMode }, transform{ transformation }, texture{ theTexture }, shader{ theShader } {}
	}
}
