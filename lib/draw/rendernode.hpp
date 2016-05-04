#ifndef LIB_DRAW_RENDERNODE_HPP
#define LIB_DRAW_RENDERNODE_HPP

#include "scenenode.hpp"
#include <lib/include/types.hpp>
#include <lib/include/color.hpp>
#include "transformable.hpp"
#include "vertexarray.hpp"

namespace sf
{
	class Texture;
}

namespace lib
{
	namespace draw
	{
		class RenderGroup;
		enum class Alignment : u8
		{
			Left = 0,
			Center = 1,
			Right = 2
		};

		class RenderNode : public SceneNode, public Transformable
		{
		public:
			explicit RenderNode(const std::string &name, const PrimitiveType primitiveType);
			virtual ~RenderNode();

			virtual u32 draw() = 0;
			virtual void setColor(const lib::draw::Color &color);
			const Color& getColor() const;

			virtual Rectf32 getLocalBounds();
			virtual Rectf32 getGlobalBounds();

			// Some useful shortcuts
			using Transformable::setPosition;
			void setPosition(const vector2df &pos, Alignment alignment);
			void setPositionX(const f32 x, Alignment alignment = Alignment::Left);
			void setPositionY(const f32 y, Alignment alignment = Alignment::Left);
			void setAlignment(Alignment alignment);

			virtual const sf::Texture *texture() const = 0;
			virtual const VertexArray &vertexArray() const;
			virtual void update();
		protected:
			virtual void ensureGeometryUpdate() = 0;
			void updateFillColors();
			VertexArray m_vertices;
			Rectf32 m_bounds;
			Color m_color;
			bool m_geometryNeedUpdate;
			bool m_colorsNeedUpdate;
		};
	}
}

#endif
