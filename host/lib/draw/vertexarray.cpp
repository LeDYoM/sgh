#include "vertexarray.hpp"
#include <lib/core/window.hpp>

namespace lib
{
	namespace draw
	{
		VertexArray::VertexArray() 
			: m_vertices{}, m_primitiveType{ sf::Points } {}


		VertexArray::VertexArray(sf::PrimitiveType type, std::size_t vertexCount)
			: m_vertices( vertexCount ), m_primitiveType{ type } {}

		std::size_t VertexArray::getVertexCount() const
		{
			return m_vertices.size();
		}

		Vertex &VertexArray::operator [](std::size_t index)
		{
			return m_vertices[index];
		}

		const Vertex &VertexArray::operator [](std::size_t index) const
		{
			return m_vertices[index];
		}

		void VertexArray::clear()
		{
			m_vertices.clear();
		}

		void VertexArray::resize(std::size_t vertexCount)
		{
			m_vertices.resize(vertexCount);
		}

		void VertexArray::append(const Vertex &vertex)
		{
			m_vertices.push_back(vertex);
		}

		void VertexArray::setPrimitiveType(sf::PrimitiveType type)
		{
			m_primitiveType = type;
		}

		sf::PrimitiveType VertexArray::getPrimitiveType() const
		{
			return m_primitiveType;
		}

		Rectf32 VertexArray::getBounds() const
		{
			if (!m_vertices.empty())
			{
				f32 left = m_vertices[0].position.x;
				f32 top = m_vertices[0].position.y;
				f32 right = m_vertices[0].position.x;
				f32 bottom = m_vertices[0].position.y;

				for (std::size_t i = 1; i < m_vertices.size(); ++i)
				{
					vector2df position = m_vertices[i].position;

					// Update left and right
					if (position.x < left)
						left = position.x;
					else if (position.x > right)
						right = position.x;

					// Update top and bottom
					if (position.y < top)
						top = position.y;
					else if (position.y > bottom)
						bottom = position.y;
				}

				return Rectf32(left, top, right - left, bottom - top);
			}
			else
			{
				return Rectf32{};
			}
		}
	}
}
