#include "RenderNode.hpp"
#include <lib/core/window.hpp>
#include <lib/core/log.hpp>

namespace lib
{
	namespace draw
	{
		RenderNode::RenderNode(const std::string &name, const PrimitiveType primitiveType)
			: SceneNode(name), m_vertices{ primitiveType }, m_bounds{}, m_color{ 255, 255, 255 },
			m_geometryNeedUpdate{ true }, m_colorsNeedUpdate{ true }
		{
			LOG_CONSTRUCT("Name: " + name);
		}

		RenderNode::~RenderNode()
		{
			LOG_DESTRUCT("Name: " + name());
			m_vertices.clear();
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
			for (std::size_t i = 0; i < m_vertices.getVertexCount(); ++i) {
				m_vertices[i].color = m_color;
			}
			m_colorsNeedUpdate = false;
		}

		Rectf32 RenderNode::getLocalBounds()
		{
			ensureGeometryUpdate();
			return m_bounds;
		}

		Rectf32 RenderNode::getGlobalBounds()
		{
			return transformation().transformRect(getLocalBounds());
		}

		const VertexArray &RenderNode::vertexArray() const
		{
			return m_vertices;
		}

		void RenderNode::update()
		{
			if (m_geometryNeedUpdate) {
				ensureGeometryUpdate();
			}

			if (m_colorsNeedUpdate) {
				updateFillColors();
			}
		}
	}
}
