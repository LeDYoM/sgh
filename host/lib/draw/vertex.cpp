#include "vertex.hpp"

namespace lib
{
	namespace draw
	{
		Vertex::Vertex() 
			: position{ 0, 0 }, color{ 255, 255, 255 }, texCoords{ 0, 0 } {}

		Vertex::Vertex(const sf::Vector2f& thePosition)
			: Vertex{ thePosition, { 255, 255, 255 }, { 0, 0 } } {}

		Vertex::Vertex(const sf::Vector2f& thePosition, const sf::Color& theColor)
			: Vertex{ thePosition, { theColor }, { 0, 0 } } {}

		Vertex::Vertex(const sf::Vector2f& thePosition, const sf::Vector2f& theTexCoords)
			: Vertex{ thePosition, { 255, 255, 255 }, { theTexCoords } } {}

		Vertex::Vertex(const sf::Vector2f& thePosition, const sf::Color& theColor, const sf::Vector2f& theTexCoords) 
			: position{ thePosition }, color{ theColor }, texCoords{ theTexCoords } {}
	}
}
