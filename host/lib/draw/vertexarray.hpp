#ifndef LIB_DRAW_VERTEXARRAY_HPP
#define LIB_DRAW_VERTEXARRAY_HPP

#include <SFML/Graphics/Vertex.hpp>
#include <SFML/Graphics/PrimitiveType.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <vector>


namespace lib
{
	namespace draw
	{
	class VertexArray : public sf::Drawable
	{
	public:
		VertexArray();
		explicit VertexArray(sf::PrimitiveType type, std::size_t vertexCount = 0);
		std::size_t getVertexCount() const;
		sf::Vertex& operator [](std::size_t index);
		const sf::Vertex& operator [](std::size_t index) const;
		void clear();
		void resize(std::size_t vertexCount);
		void append(const sf::Vertex& vertex);
		void setPrimitiveType(sf::PrimitiveType type);
		sf::PrimitiveType getPrimitiveType() const;
		sf::FloatRect getBounds() const;
	private:
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	private:
		std::vector<sf::Vertex> m_vertices;
		sf::PrimitiveType m_primitiveType;
	};

} // namespace sf


#endif
