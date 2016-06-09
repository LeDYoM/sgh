#include "RenderNode.hpp"
#include <lib/core/window.hpp>
#include <lib/core/log.hpp>

namespace lib
{
	namespace draw
	{
		RenderNode::RenderNode(const std::string &name, const PrimitiveType primitiveType)
			: SceneNode(name), m_vertices{ primitiveType }, m_bounds{}, 
			color{ Color{ 255, 255, 255 } }, 
			m_geometryNeedUpdate{ true }
		{
			LOG_CONSTRUCT("Name: " + name);
		}

		RenderNode::~RenderNode()
		{
			LOG_DESTRUCT("Name: " + name());
			m_vertices.clear();
		}

		void RenderNode::updateFillColors()
		{
			for (std::size_t i = 0; i < m_vertices.getVertexCount(); ++i) {
				m_vertices[i].color = color;
			}
			color.resetChanged();
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
			Transformable::update();

			if (m_geometryNeedUpdate) {
				ensureGeometryUpdate();
			}

			if (color.changed()) {
				updateFillColors();
			}
		}
	}
}
