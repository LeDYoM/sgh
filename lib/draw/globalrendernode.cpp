#include "globalrendernode.hpp"
#include <lib/core/window.hpp>
#include <lib/core/log.hpp>

namespace lib
{
	namespace draw
	{
		GlobalRenderNode::GlobalRenderNode()
			: 
			color{ Color{ 255, 255, 255 } }, 
			m_geometryNeedUpdate{ true }
		{
			LOG_CONSTRUCT_NOPARAMS;
		}

		GlobalRenderNode::~GlobalRenderNode()
		{
			LOG_DESTRUCT_NOPARAMS;
			m_vertices.clear();
		}

		void GlobalRenderNode::updateFillColors()
		{
			for (std::size_t i = 0; i < m_vertices.getVertexCount(); ++i) {
				m_vertices[i].color = color;
			}
			color.resetChanged();
		}

		Rectf32 GlobalRenderNode::getLocalBounds()
		{
			ensureGeometryUpdate();
			return m_bounds;
		}

		Rectf32 GlobalRenderNode::getGlobalBounds()
		{
			return transformation().transformRect(getLocalBounds());
		}

		const VertexArray &GlobalRenderNode::vertexArray() const
		{
			return m_vertices;
		}

		void GlobalRenderNode::update()
		{
			if (m_geometryNeedUpdate) {
				ensureGeometryUpdate();
			}

			if (color.changed()) {
				updateFillColors();
			}
		}
	}
}
