#include "rendernode.hpp"
#include <lib/core/window.hpp>
#include <lib/core/log.hpp>
#include "renderstates.hpp"
#include <lib/core/convops.hpp>

namespace lib
{
	namespace draw
	{
		RenderNode::RenderNode(RenderGroup *const p_parent, const std::string &name, const PrimitiveType primitiveType)
			: SceneNode(p_parent, name), m_vertices{ primitiveType }, m_bounds{}, 
			color{ Color{ 255, 255, 255 } }, m_geometryNeedUpdate{ true }, m_renderStates{ new priv::RenderStates }
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
			for (std::size_t i = 0; i < m_vertices.size(); ++i) {
				m_vertices[i].color = color();
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

		void RenderNode::updateRenderStates()
		{
			m_renderStates->transform = convert(globalTransformation());
			m_renderStates->blendMode = sf::BlendMode();
			m_renderStates->shader = nullptr;
			m_renderStates->texture = texture();
		}

	}
}
