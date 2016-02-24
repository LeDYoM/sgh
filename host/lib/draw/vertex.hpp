#ifndef LIB_DRAW_VERTEX_HPP
#define LIB_DRAW_VERTEX_HPP

#include <SFML/Graphics/Export.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/System/Vector2.hpp>

namespace lib
{
	namespace draw
	{
		class Vertex
		{
		public:
			Vertex();
			Vertex(const sf::Vector2f& thePosition);
			Vertex(const sf::Vector2f& thePosition, const sf::Color& theColor);
			Vertex(const sf::Vector2f& thePosition, const sf::Vector2f& theTexCoords);
			Vertex(const sf::Vector2f& thePosition, const sf::Color& theColor, const sf::Vector2f& theTexCoords);

			sf::Vector2f position;
			sf::Color color;
			sf::Vector2f texCoords;
		};
	}
}

#endif
