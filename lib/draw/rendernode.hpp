#ifndef LIB_DRAW_RENDERNODE_HPP
#define LIB_DRAW_RENDERNODE_HPP

#include "scenenode.hpp"
#include <lib/include/types.hpp>
#include <lib/include/color.hpp>
#include <lib/include/properties.hpp>
#include "vertexarray.hpp"

namespace lib
{
	namespace drivers::render {
		class Texture;
	}
	namespace draw
	{
		class RenderGroup;
		class Texture;
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

			NotifableProperty<Color> color;

			virtual Rectf32 getLocalBounds();
			virtual Rectf32 getGlobalBounds();

			inline const VertexArray &vertexArray() const { return m_vertices; }
			virtual void update() override;

			void updateRenderStates();
			const priv::RenderStates &renderStates() const { return *m_renderStates; }

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
