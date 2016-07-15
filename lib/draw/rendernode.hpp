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
		namespace priv
		{
			class RenderStates;
		}

		enum class BlendType : u32
		{
			Zero,
			One,
			SrcColor,
			OneMinusSrcColor,
			DstColor,
			OneMinusDstColor,
			SrcAlpha,
			OneMinusSrcAlpha,
			DstAlpha,
			OneMinusDstAlpha,
		};
		class RenderNode : public SceneNode
		{
		public:
			explicit RenderNode(RenderGroup *const p_parent, const std::string &name, const PrimitiveType primitiveType);
			virtual ~RenderNode();

			virtual u32 draw() = 0;
			NotifableProperty<Color> color;

			virtual Rectf32 getLocalBounds();
			virtual Rectf32 getGlobalBounds();

			virtual const sf::Texture *texture() const = 0;
			virtual const VertexArray &vertexArray() const;
			virtual void update() override;

			void updateRenderStates();

		protected:
			virtual void ensureGeometryUpdate() = 0;
			void updateFillColors();
			VertexArray m_vertices;
			Rectf32 m_bounds;
			bool m_geometryNeedUpdate;

		private:
			uptr<priv::RenderStates> m_renderStates;
		};
	}
}

#endif
