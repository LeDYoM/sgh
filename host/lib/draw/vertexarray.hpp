#ifndef LIB_DRAW_VERTEXARRAY_HPP
#define LIB_DRAW_VERTEXARRAY_HPP

#include <SFML/Graphics/PrimitiveType.hpp>
#include "idrawable.hpp"
#include "vertex.hpp"
#include <vector>
#include <lib/include/rect.hpp>

namespace lib
{
	namespace draw
	{
		class VertexArray
		{
		public:
			VertexArray();
			explicit VertexArray(sf::PrimitiveType type, std::size_t vertexCount = 0);
			std::size_t getVertexCount() const;
			Vertex &operator [](std::size_t index);
			const Vertex &operator [](std::size_t index) const;
			void clear();
			void resize(std::size_t vertexCount);
			void append(const Vertex &vertex);
			void setPrimitiveType(sf::PrimitiveType type);
			sf::PrimitiveType getPrimitiveType() const;
			Rectf32 getBounds() const;
		private:
			std::vector<Vertex> m_vertices;
			sf::PrimitiveType m_primitiveType;
		};
	}
}

#endif
