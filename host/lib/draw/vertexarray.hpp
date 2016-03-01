#ifndef LIB_DRAW_VERTEXARRAY_HPP
#define LIB_DRAW_VERTEXARRAY_HPP

#include "idrawable.hpp"
#include "vertex.hpp"
#include <lib/include/types.hpp>
#include <vector>

namespace lib
{
	namespace draw
	{
		enum PrimitiveType
		{
			Points,
			Lines,
			LinesStrip,
			Triangles,
			TrianglesStrip,
			TrianglesFan,
		};

		class VertexArray
		{
		public:
			VertexArray();
			explicit VertexArray(PrimitiveType type, std::size_t vertexCount = 0);
			std::size_t getVertexCount() const;
			Vertex &operator [](std::size_t index);
			const Vertex &operator [](std::size_t index) const;
			void clear();
			void resize(std::size_t vertexCount);
			void append(const Vertex &vertex);
			void setPrimitiveType(const PrimitiveType type);
			PrimitiveType getPrimitiveType() const;
			Rectf32 getBounds() const;
		private:
			std::vector<Vertex> m_vertices;
			PrimitiveType m_primitiveType;
		};
	}
}

#endif
