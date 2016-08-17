#ifndef __LIB_ELLIPSESHAPE_HPP__
#define __LIB_ELLIPSESHAPE_HPP__

#include <lib/include/types.hpp>
#include <lib/include/properties.hpp>
#include "rendernode.hpp"

namespace lib
{
	namespace drivers
	{
		namespace render
		{
			class Texture;
		}
	}
	namespace draw
	{
		class NodeShape : public RenderNode
		{
		public:
			enum class NodeMode : u8
			{
				Shape = 0,
				Sprite = 1,
			} _mode{ NodeMode::Shape };
//			explicit NodeShape(RenderGroup *const p_parent, const std::string &name, const vector2df& size, const u32 pointCount=4,const NodeMode mode=NodeMode::Shape);
			explicit NodeShape(RenderGroup *const p_parent, const std::string &name);
			virtual ~NodeShape();

			Property<vector2df> size;
			Property<u16> points;
			vector2df getPoint(const u32 index) const;

		protected:
			virtual void ensureGeometryUpdate() override;
			void setTexture_(const Texture* texture, bool resetRect = false);
			virtual void update() override;
			void updateTexCoords();

		private:
			lib::vector2df _size;
			lib::u32 m_pointCount;
			Rects32 m_textureRect;
		};
	}
}

#endif
