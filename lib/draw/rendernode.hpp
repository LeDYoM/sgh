#ifndef LIB_DRAW_RENDERNODE_HPP
#define LIB_DRAW_RENDERNODE_HPP

#include "scenenode.hpp"
#include <lib/include/types.hpp>
#include <lib/include/color.hpp>
#include <lib/include/properties.hpp>
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
		class RenderNode : public SceneNode
		{
		public:
			explicit RenderNode(const std::string &name, const PrimitiveType primitiveType);
			virtual ~RenderNode();

			virtual u32 draw() = 0;
			NotifableProperty<Color> color;

			virtual Rectf32 getLocalBounds();
			virtual Rectf32 getGlobalBounds();

			virtual const sf::Texture *texture() const = 0;
			virtual const VertexArray &vertexArray() const;
			virtual void update();
			virtual void updateForFrame();

		protected:
			virtual void ensureGeometryUpdate() = 0;
			void updateFillColors();
			VertexArray m_vertices;
			Rectf32 m_bounds;
			bool m_geometryNeedUpdate;
		};
	}
}

#endif
