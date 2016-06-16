#ifndef LIB_DRAW_VERTEXARRAY_HPP
#define LIB_DRAW_VERTEXARRAY_HPP

#include "vertex.hpp"
#include <lib/include/types.hpp>
#include <vector>

namespace lib
{
	namespace draw
	{
		using BasicVertexArray = std::vector<Vertex>;
		enum class PrimitiveType
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
			explicit VertexArray(const PrimitiveType type, const std::size_t vertexCount = 0);
			Vertex &operator [](const std::size_t index);
			const Vertex &operator [](const std::size_t index) const;
			void clear();
			void resize(const std::size_t vertexCount);
			void append(const Vertex &vertex);
			void setPrimitiveType(const PrimitiveType type);
			PrimitiveType getPrimitiveType() const;
			Rectf32 getBounds() const;
			inline const BasicVertexArray *data() const { return &m_vertices; }
			inline const BasicVertexArray::size_type size() const { return m_vertices.size(); }
		private:
			BasicVertexArray m_vertices;
			PrimitiveType m_primitiveType;
		};
	}
}

#endif
