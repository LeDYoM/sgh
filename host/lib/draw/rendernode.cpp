#include "RenderNode.hpp"
#include <lib/core/window.hpp>
#include <lib/core/log.hpp>

namespace lib
{
	namespace draw
	{
		RenderNode::RenderNode(const std::string &name, const sf::PrimitiveType primitiveType)
			: HasName{ name }, m_vertices{ primitiveType }, m_bounds{}, m_color{ 255, 255, 255 }, m_geometryNeedUpdate{ true }
		{
			LOG_CONSTRUCT("Name: " << name << " of type");
		}

		RenderNode::~RenderNode()
		{
		}

		void RenderNode::setPosition(const vector2df &pos, Alignment alignment)
		{
			switch (alignment)
			{
			default:
			case lib::draw::Alignment::Left:
				Transformable::setPosition(pos);
				break;
			case lib::draw::Alignment::Center:
				Transformable::setPosition(lib::vector2df{ pos.x - (getLocalBounds().width / 2.0f), pos.y - (getLocalBounds().height / 2.0f) });
				break;
			case lib::draw::Alignment::Right:
				Transformable::setPosition(lib::vector2df{ pos.x - (getLocalBounds().width), pos.y - (getLocalBounds().height) });
				break;
			}
		}

		void RenderNode::setPositionX(const f32 x, Alignment alignment /*= Alignment::Left*/)
		{
			const lib::vector2df position( Transformable::position() );
			switch (alignment)
			{
			default:
			case lib::draw::Alignment::Left:
				Transformable::setPosition(lib::vector2df{ x, position.y });
				break;
			case lib::draw::Alignment::Center:
			{
				Transformable::setPosition(lib::vector2df{ x - (getLocalBounds().width / 2.0f), position.y });
			}
				break;
			case lib::draw::Alignment::Right:
				Transformable::setPosition(lib::vector2df{ x - (getLocalBounds().width), position.y });
				break;
			}
		}

		void RenderNode::setPositionY(const f32 y, Alignment alignment /*= Alignment::Left*/)
		{
			const lib::vector2df position(Transformable::position());
			switch (alignment)
			{
			default:
			case lib::draw::Alignment::Left:
				Transformable::setPosition(lib::vector2df{ position.x, y });
				break;
			case lib::draw::Alignment::Center:
				Transformable::setPosition(lib::vector2df{ position.x, y - (getLocalBounds().height / 2.0f) });
				break;
			case lib::draw::Alignment::Right:
				Transformable::setPosition(lib::vector2df{ position.x, y - (getLocalBounds().height) });
				break;
			}
		}

		void RenderNode::setAlignment(Alignment alignment)
		{
			setPosition(position(), alignment);
		}

		void RenderNode::setColor(const Color& color)
		{
			m_color = color;
			updateFillColors();
		}

		const Color &RenderNode::getColor() const
		{
			return m_color;
		}

		void RenderNode::updateFillColors()
		{
			// Change vertex colors directly, no need to update whole geometry
			// (if geometry is updated anyway, we can skip this step)
//			if (!m_geometryNeedUpdate)
//			{
				for (std::size_t i = 0; i < m_vertices.getVertexCount(); ++i)
					m_vertices[i].color = m_color;
//			}
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
	}
}
