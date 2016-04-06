#include "RenderNode.hpp"
#include <lib/core/window.hpp>
#include <lib/core/log.hpp>

namespace lib
{
	namespace draw
	{
		RenderNode::RenderNode(const std::string &name, const PrimitiveType primitiveType)
			: Node( name ), m_vertices{ primitiveType }, m_bounds{}, m_color{ 255, 255, 255 }, 
			m_geometryNeedUpdate{ true }, m_colorsNeedUpdate{ true }
		{
			LOG_CONSTRUCT("Name: " + name);
		}

		RenderNode::~RenderNode()
		{
			LOG_DESTRUCT("Name: " + name());
			m_vertices.clear();
		}

		void RenderNode::setPosition(const vector2df &pos)
		{
			Transformable::setPosition(pos);
		}

		void RenderNode::setPositionX(const f32 x)
		{
			setPosition(lib::vector2df{ x, position().y });
		}

		void RenderNode::setPositionY(const f32 y)
		{
			setPosition(lib::vector2df{ position().x, y });
		}

		void RenderNode::setColor(const Color& color)
		{
			m_color = color;
			m_colorsNeedUpdate = true;
		}

		const Color &RenderNode::getColor() const
		{
			return m_color;
		}

		void RenderNode::updateFillColors()
		{
			for (std::size_t i = 0; i < m_vertices.getVertexCount(); ++i)
				m_vertices[i].color = m_color;
		}

		Rectf32 RenderNode::getLocalBounds()
		{
			updateGeometryIfNecessary();
			return m_bounds;
		}

		Rectf32 RenderNode::getGlobalBounds()
		{
			return transformation().transformRect(getLocalBounds());
		}

		void RenderNode::updateGeometryIfNecessary()
		{
			if (m_geometryNeedUpdate)
			{
				ensureGeometryUpdate();
			}

			if (m_colorsNeedUpdate)
			{
				updateFillColors();
				m_colorsNeedUpdate = false;
			}
		}

	}
}
