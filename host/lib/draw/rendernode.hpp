#ifndef LIB_DRAW_RENDERNODE_HPP
#define LIB_DRAW_RENDERNODE_HPP

#include "inameddrawable.hpp"
#include <lib/include/types.hpp>
#include <lib/include/color.hpp>
#include "transformable.hpp"
#include "vertexarray.hpp"
#include "iparentable.hpp"

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

		class RenderNode : public IParentable<RenderGroup>, public INamedDrawable, public Transformable
		{
		public:
			explicit RenderNode(const std::string &name, const PrimitiveType primitiveType);
			virtual ~RenderNode();

			virtual u32 draw(lib::draw::RenderStates &states) = 0;
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

			void updateGeometryIfNecessary();
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
